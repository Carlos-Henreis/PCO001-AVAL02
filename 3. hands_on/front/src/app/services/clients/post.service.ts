import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';

import { environment } from '@env/environment';
import { AuthService } from '../auth/auth.service';


@Injectable({
  providedIn: 'root'
})
export class PostService {
  private apiUrl = `${environment.httpServer}/api/posts`

  constructor(private http: HttpClient, private authService: AuthService) {}

  getPosts(): Observable<any> {
    return this.http.get<any>(this.apiUrl);
  }

  addPost(post: any): Observable<any> {
    return this.http.post<any>(this.apiUrl, post);
  }

  likePost(postId: string): Observable<any> {
    const userId = this.authService.getUser().matricula;
    return this.http.post<any>(`${this.apiUrl}/${postId}/like`, { userId });
  }
}
