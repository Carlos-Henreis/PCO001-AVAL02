import { Injectable } from '@angular/core';
import { HttpInterceptor, HttpRequest, HttpHandler, HttpEvent } from '@angular/common/http';
import { Observable } from 'rxjs';

import { AuthService } from '../services/auth/auth.service';

@Injectable()
export class AuthInterceptor implements HttpInterceptor {

  constructor(private authService: AuthService) {}

  intercept(req: HttpRequest<any>, next: HttpHandler): Observable<HttpEvent<any>> {
    const authToken = this.authService.getToken() || '';

    // Verifique se a URL contém a rota de login
    if (req.url.includes('/login')) {
      // Se for a rota de login, passe a requisição sem modificar
      return next.handle(req);
    }

    // Clone a requisição e adicione o cabeçalho de autenticação
    const authReq = req.clone({
      headers: req.headers.set('Authorization', authToken)
    });

    // Envie a requisição clonada com o cabeçalho de autenticação
    return next.handle(authReq);
  }
}