import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { FormsModule } from '@angular/forms';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';

import { ToolbarComponent } from '@app/components/toolbar/toolbar.component';
import { AppRoutingModule } from '@app/app-routing.module';
import { AppComponent } from '@app/app.component';
import { LoginComponent } from '@app/components/login/login.component';
import { PostFeedComponent } from '@app/components/post-feed/post-feed.component';
import { AddPostComponent } from '@app/components/add-post/add-post.component';
import { OnlineUsersComponent } from '@app/components/online-users/online-users.component';
import { HttpClientModule, HTTP_INTERCEPTORS } from '@angular/common/http';
import { AuthInterceptor } from '@app/interceptor/auth.interceptor';
import { ErrorInterceptor } from '@app/interceptor/error.interceptor';
import { WebsocketService } from './services/websocket/websocket.service';

import { MatBadgeModule } from '@angular/material/badge';
import { MatSnackBarModule } from '@angular/material/snack-bar';
import { MatListModule } from '@angular/material/list';
import { MatIconModule } from '@angular/material/icon';
import { MatFormFieldModule } from '@angular/material/form-field'; // Importe MatFormFieldModule
import { MatInputModule } from '@angular/material/input'; // Importe MatInputModule
import { MatButtonModule } from '@angular/material/button'
import { MatToolbarModule } from '@angular/material/toolbar';
import { MatMenuModule } from '@angular/material/menu';
import { MatTooltipModule} from '@angular/material/tooltip';
import {MatProgressBarModule} from '@angular/material/progress-bar';
import {MatProgressSpinnerModule} from '@angular/material/progress-spinner';
import {MatCardModule} from '@angular/material/card';


@NgModule({
  declarations: [
    AppComponent,
    LoginComponent,
    PostFeedComponent,
    AddPostComponent,
    ToolbarComponent,
    OnlineUsersComponent
  ],
  imports: [
    MatProgressSpinnerModule,
    MatProgressBarModule,
    MatTooltipModule,
    MatBadgeModule,
    MatSnackBarModule,
    MatMenuModule,
    MatToolbarModule,
    MatCardModule,
    MatListModule,
    MatIconModule,
    BrowserModule,
    AppRoutingModule,
    HttpClientModule,
    FormsModule,
    MatFormFieldModule,
    MatInputModule,
    MatButtonModule,
    BrowserAnimationsModule
  ],
  providers: [
    {
      provide: HTTP_INTERCEPTORS,
      useClass: AuthInterceptor,
      multi: true
    },
    {
      provide: HTTP_INTERCEPTORS,
      useClass: ErrorInterceptor,
      multi: true
    },
    WebsocketService
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
