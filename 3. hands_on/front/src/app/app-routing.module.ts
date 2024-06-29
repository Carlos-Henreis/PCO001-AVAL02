// app-routing.module.ts
import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { LoginComponent } from '@app/components/login/login.component';
import { PostFeedComponent } from '@app/components/post-feed/post-feed.component';
import { AuthGuard } from '@app/auth.guard';

const routes: Routes = [
  { path: 'login', component: LoginComponent },
  { path: 'feed', component: PostFeedComponent, canActivate: [AuthGuard] },
  { path: '', redirectTo: '/feed', pathMatch: 'full' },
  { path: '**', redirectTo: '/feed' } // Rota padrão para redirecionar para o feed se a rota não existir
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
