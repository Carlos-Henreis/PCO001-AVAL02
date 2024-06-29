import { Component } from '@angular/core';
import { Router } from '@angular/router';
import { AuthService } from '@app/services/auth/auth.service';
import { MatSnackBar } from '@angular/material/snack-bar';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent {
  matricula: string = '';
  loading: boolean = false;

  constructor(private authService: AuthService, private router: Router, private snackBar: MatSnackBar) {}

  login(): void {
    this.loading = true;
    this.authService.login(this.matricula).subscribe(
      resp => {
        localStorage.setItem('token', resp.token);
        this.loading = false;
        this.router.navigate(['/posts']);
      },
      error => {
        this.loading = false;
        this.showErrorAlert()
        console.error('Login failed', error);
      }
    );
  }

  showErrorAlert(): void {
    this.snackBar.open('Erro! Usuário não está matriculado na disciplina PCO001', '[FECHAR]', {
      duration: 30000,
      panelClass: 'error-alert',
    });
  }

}
