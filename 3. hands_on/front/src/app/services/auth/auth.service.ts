import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable, finalize } from 'rxjs';
import { jwtDecode } from "jwt-decode";
import { Router } from '@angular/router';

import { environment } from '@env/environment';

@Injectable({
  providedIn: 'root'
})
export class AuthService {
  private apiUrl = `${environment.httpServer}/api`;

  constructor(private http: HttpClient, private router: Router) {}

  login(matricula: string): Observable<any> {
    return this.http.post<any>(`${this.apiUrl}/login`, { matricula });
  }

  logoutClient(matricula: string): Observable<any> {
    return this.http.post<any>(`${this.apiUrl}/logout`, { matricula });
  }

  logout(): void {
    const user = this.getUser();
    if (!this.isLoggedIn()) {
      this.router.navigate(['/login']);
    }
    else {
      this.logoutClient(user.matricula).pipe(
        finalize(() => {
          this.router.navigate(['/login']);
        })
      ).subscribe(
        () => {
          localStorage.removeItem('token');
        },
        error => {
          console.error('Logout failed', error);
        }
      );
    }
  }

  isLoggedIn(): boolean {
    return !!localStorage.getItem('token'); // Retorna true se existir um usuário e um token no localStorage
  }

  getToken(): string | null {
    return localStorage.getItem('token'); // Retorna o token do localStorage
  }

  getUser(): any {
    // Retornar o nome e matricula do usupario que está no token
    const token = this.getToken();
    if (token) {
      const decodedToken: any = jwtDecode(token);

      return {
        matricula: decodedToken.matricula!,
        nome: decodedToken.nome!
      };
    }
    return { matricula: '', nome: ''};
  }
}
