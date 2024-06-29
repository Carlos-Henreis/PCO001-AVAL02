import { Component } from '@angular/core';
import { Router } from '@angular/router';
import { AuthService } from '../../services/auth/auth.service';

@Component({
  selector: 'app-toolbar',
  templateUrl: './toolbar.component.html',
  styleUrls: ['./toolbar.component.css']
})
export class ToolbarComponent {
  // Adicione a propriedade userName recebendo o nome do usuário logado
  userName: string = '';

  constructor(private router: Router, private authService: AuthService) {}

  ngOnInit(): void {
    // Implemente a lógica para buscar o nome do usuário logado
    const user = this.authService.getUser();
    this.userName = user.nome;
  }

  logout(): void {
    // Implemente a lógica de logout aqui
      this.authService.logout();
  }
}