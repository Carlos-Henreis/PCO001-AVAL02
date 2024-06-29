# Hands On com Neo4j

## Descrição

Este projeto é uma introdução prática ao Neo4j, um banco de dados orientado a grafo.

## Pré-requisitos

- Docker
- NodeJs
- npm

### Instalação Neo4j com Docker

1. **Instalar Docker**:
   - Siga as instruções de instalação para o Docker no site oficial: [Docker Installation](https://docs.docker.com/get-docker/).

2. **Baixar e executar a imagem do Neo4j**:
   - Execute o comando abaixo no seu terminal para baixar e executar a imagem do Neo4j:

     ```sh
     docker run \
         --name neo4j \
         -p7474:7474 -p7687:7687 \
         -d \
         -e NEO4J_AUTH=neo4j/bananinha \
         neo4j:latest
     ```

3. **Verificar se o container está rodando**:
   - Execute `docker ps` para verificar se o container Neo4j está ativo.

4. **Acessar a interface web do Neo4j**:
   - Abra seu navegador e vá para `http://localhost:7474`. Use as credenciais `neo4j` e `bananinha` para fazer login.

### Efetuar carga dos usuários

Em `http://localhost:7474/browser/`

```cypher
CREATE (:User {matricula: "0001", nome: "Fulano"})
CREATE (:User {matricula: "0002", nome: "Sicrano"})
```
# Execução

## Servidor

1. Acesse `server/`

```
cd server/
```

2. Crie um arquivo `.env` com as seguintes variáveis

```env
NEO4J_URI=bolt://localhost:7687
NEO4J_USER=neo4j
NEO4J_PASSWORD=bananinha
JWT_SECRET=sua_chave_secreta
```

3. Instale os pacotes

```
npm install
```

4. inicie o projeto

```
npm run dev
```

## Front

1. Acesse `front/`

```
cd front/
```

2. Instale os pacotes

```
npm install
```

3. inicie o projeto

```
ng serve
```

# Acesso

Basta acessar `localhost:4200` no seu navegador e logar com `0001` ou `0002`
