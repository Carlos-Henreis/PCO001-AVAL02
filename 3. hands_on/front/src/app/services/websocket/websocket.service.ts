import { Injectable } from '@angular/core';
import { Observable, Subject } from 'rxjs';
import { environment } from '@env/environment';
import { AuthService } from '../auth/auth.service';

@Injectable({
  providedIn: 'root'
})
export class WebsocketService {
  private subject: Subject<any> | undefined;
  private ws: WebSocket | undefined;

  constructor(private authService: AuthService) {}

  public connect(): Subject<any> {
    console.log('Connecting to WebSocket');
    console.log('Subject:', this.subject);
    if (!this.subject) {
      const token = this.authService.getToken();
      const url = environment.wsServer;
      this.subject = this.create(url, token);
    }
    return this.subject;
  }

  private create(url: string, token: string | null): Subject<any> {
    if (!this.ws) {
      this.ws = new WebSocket(`${url}?authorization=${token}`);

      const observable = new Observable(observer => {
        this.ws!.onopen = () => {
          console.log('WebSocket connection opened');
        };
        this.ws!.onmessage = (event) => {
          const data = JSON.parse(event.data);
          observer.next(data);
        };
        this.ws!.onerror = (error) => {
          console.error('WebSocket error:', error);
          observer.error(error);
        };
        this.ws!.onclose = (event) => {
          console.log('WebSocket connection closed');
          this.authService.logout();
          observer.complete();
        };
        return () => {
          if (this.ws) {
            this.ws.close();
            this.ws = undefined;
          }
        };
      });

      const observer = {
        next: (data: Object) => {
          if (this.ws && this.ws.readyState === WebSocket.OPEN) {
            this.ws.send(JSON.stringify(data));
          }
        }
      };

      this.subject = Subject.create(observer, observable);
    }
    return this.subject!;
  }

  public sendMessage(message: any) {
    if (this.ws && this.ws.readyState === WebSocket.OPEN) {
      this.ws.send(JSON.stringify(message));
    }
  }

  public disconnect() {
    if (this.ws) {
      this.ws.close();
      this.ws = undefined;
      this.subject = undefined;
    }
  }
}
