# Api Demo Grafo

* [Descricao](#descricao)
* [Endpoints REST](#endpoints-rest)
  * [Autenticação](#autenticação)
  * [Posts](#posts)
  * [Likes](#likes)
* [WebSocket](#websocket)
    * [Conexão](#conexão)
    * [Eventos](#eventos)
    * [Mensagens](#mensagens)
        * [Broadcast de Usuários Online](#broadcast-de-usuários-online)
        * [Broadcast de Novo Post](#broadcast-de-novo-post)
        * [Broadcast de Like](#broadcast-de-like)


## Descrição

Esta documentação cobre tanto a API RESTful quanto a interface WebSocket da nossa aplicação. A API RESTful integra com o banco de dados orientado a grafos Neo4j, enquanto o WebSocket é usado para comunicação em tempo real.

## Endpoints REST

### Autenticação

**POST** `/api/login`: Autentica o usuário e retorna um token JWT.
Para autenticar, envie um JSON no corpo da requisição com número de matricula do usuário.

```json
{
    "matricula": "0001"
}
```

* Retorno:

```json
{
    "token": "seu_token_jwt"
}
```

**POST** `/api/logout`: Desloga o usuário.

```json
{
    "matricula": "0001"
}
```

* Retorno:

```json
{
	"matricula": "0001",
	"nome": "SANDRO CARVALHO IZIDORO"
}
```


### Posts

**GET** `/api/posts`: Retorna todos os posts.

```curl
curl -X GET http://localhost:3000/api/posts
-H "Authorization: seu_token_jwt"
```

* Retorno:

```json
[
	{
		"id": "d569f60b-763a-4a1e-8f51-ca8c18d9d6db",
		"content": "Post 1",
		"timestamp": 1718568623505,
		"user": "User 1",
		"likes": 3
	},
    {
        "id": "d569f60b-763a-4a1e-8f51-ca8c18d9d6db",
        "content": "Post 2",
        "timestamp": 1718568623505,
        "user": "User 2",
        "likes": 5
    }
]
```

**POST** `/api/posts`: Cria um novo post.

```json
{
    "content": "Post 1",
    "userId": "0001"
}
```

* Retorno:

```json
{
    "id": "d569f60b-763a-4a1e-8f51-ca8c18d9d6db",
    "content": "Post 1",
    "timestamp": 1718568623505,
    "user": "User 1",
    "likes": 0
}
```

### Likes

**POST** `/api/posts/:id/like`: Adiciona um like ao post.

```json
{
    "userId": "0001"
}
```

* Retorno:

```json
{
	"message": "Post liked successfully"
}
```

## WebSocket

### Conexão

Para conectar ao WebSocket, use o seguinte URL:

`ws://localhost:3000?authorization=seu_token`

### Eventos
#### Conexão

Ao conectar, o cliente deve fornecer o token de autenticação na query string. Se o token for válido, a conexão será estabelecida.

#### Desconexão

Quando o cliente se desconecta, ele será removido da lista de usuários online.

### Mensagens

### Broadcast de Usuários Online

Os usuários online serão enviados para todos os clientes conectados sempre que houver uma mudança.

* Exemplo de Mensagem Recebida
```json
{
	"type": "USERS_LOGGED_IN",
	"users_logged_in": [
		{
			"matricula": "0001",
			"nome": "Fulano"
		},
        {
            "matricula": "0002",
            "nome": "Sicrano"
        }
	]
}
```

### Broadcast de Novo Post

Quando um novo post é criado, ele será enviado para todos os clientes conectados.

* Exemplo de Mensagem Recebida
```json
{
    "type": "NEW_POST",
    "post": {
        "id": "d569f60b-763a-4a1e-8f51-ca8c18d9d6db",
        "content": "Post 1",
        "timestamp": 1718568623505,
        "user": "User 1",
        "likes": 0
    }
}
```

### Broadcast de Like

Quando um post recebe um like, é enviado para todos os clientes conectados.

* Exemplo de Mensagem Recebida
```json
{
	"type": "LIKE_POST",
	"postId": "3fb7da3d-2da7-4a0a-84f9-490685acade9"
}
```
