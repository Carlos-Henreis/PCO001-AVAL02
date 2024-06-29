import { Component } from '@angular/core';
import { MatSnackBar } from '@angular/material/snack-bar';
import { PostService } from '@app/services/clients/post.service';
import { AuthService } from '@app/services/auth/auth.service';

@Component({
  selector: 'app-add-post',
  templateUrl: './add-post.component.html',
  styleUrls: ['./add-post.component.css']
})
export class AddPostComponent {
  content: string = '';
  loading: boolean = false;

  constructor(private postService: PostService, private snackBar: MatSnackBar, private authService: AuthService) {}

  addPost(): void {
    if (this.content.trim()) {
      this.loading = true;
      const user = this.authService.getUser();
      const post = { userId: user.matricula, content: this.content };
      this.postService.addPost(post).subscribe(response => {
        this.content = '';
        this.loading = false;
      });
    } else {
      this.showErrorAlert();
    }
  }

  showErrorAlert(): void {
    this.snackBar.open('O conteúdo da postagem não pode ser vazio', '[FECHAR]', {
      duration: 30000,
      panelClass: 'error-alert',
    });
  }
}
