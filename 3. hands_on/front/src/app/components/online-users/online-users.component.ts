import { Component, Input } from '@angular/core';

@Component({
  selector: 'app-online-users',
  templateUrl: './online-users.component.html',
  styleUrls: ['./online-users.component.css']
})
export class OnlineUsersComponent {

  @Input() listUsersLogged: any[] = [];
  onlineUsersSubscription: any;

  constructor() {}

}
