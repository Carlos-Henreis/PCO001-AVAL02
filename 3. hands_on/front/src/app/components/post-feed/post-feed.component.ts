import { Component, OnInit, HostListener } from '@angular/core';
import { PostService } from '@app/services/clients/post.service';
import { Subscription } from 'rxjs';

import { WebsocketService } from '@app/services/websocket/websocket.service';


@Component({
  selector: 'app-post-feed',
  templateUrl: './post-feed.component.html',
  styleUrls: ['./post-feed.component.css']
})
export class PostFeedComponent implements OnInit {

  postSubscription: Subscription | null = null;

  loading = true;
  posts: any[] = [];
  listUsersLogged: any[] = [];
  isScrolled = false;

  constructor(private postService: PostService, private websocketService: WebsocketService) {}

  ngOnInit(): void {
    console.log('PostFeedComponent initialized');
    this.postSubscription = this.websocketService.connect()
      .subscribe((data) => {
        if (data.type === 'NEW_POST') {
          this.posts.unshift(data.post);
        } else if (data.type === 'LIKE_POST') {
          const post = this.posts.find(p => p.id === data.postId);
          if (post) {
            post.likes++;
          }
        } else if (data.type === 'USERS_LOGGED_IN') {
          this.listUsersLogged = data.users_logged_in;
        }
      });
      // Carregar os posts do servidor
      this.loadPosts();
  }

  ngOnDestroy(): void {
    if (this.postSubscription) {
      this.websocketService.disconnect();
    }
  }


  loadPosts() {
    this.loading = true;
    this.postService.getPosts().subscribe(posts => {
      this.posts = posts;
      this.loading = false;
    }
  );
  }

  likePost(postId: string): void {
    this.postService.likePost(postId).subscribe(response => {
      console.log('Post liked:', response);
    });
  }

  scrollToTop(): void {
    window.scrollTo({ top: 0, behavior: 'smooth' });
  }

  @HostListener('window:scroll', [])
  onWindowScroll() {
    // Verificar a quantidade de rolagem vertical
    this.isScrolled = window.scrollY > 100; // O FAB aparecerá após 200px de rolagem
  }

  getInitials(name: string): string {
    const nameArray = name.split(' ');
    let initials = nameArray[0].charAt(0).toUpperCase();
    if (nameArray.length > 1) {
      initials += nameArray[1].charAt(0).toUpperCase();
    }
    return initials;
  }
}
