# EasyContact API Document v0

This API document complies to RESTful API with following HTTP verbs:

|Verb     |Function                         |
|---------|---------------------------------|
|`GET`    | retrieve (a) resource(s)        |
|`POST`   | create (a) resource(s)          |
|`PUT`    | update (a) resource(s)          |
|`DELETE` | remove (an) existing resource(s)|

The server should also reply correct status codes:

|Code    |Description                        |
|--------|-----------------------------------|
|`200`   | OK                                |
|`201`   | Created                           |
|`202`   | Processed (updated/deleted)       |
|`400`   | Bad Request                       |
|`401`   | Unauthorized                      |
|`403`   | Forbidden                         |
|`404`   | Resource not found                |
|`406`   | Content-type error                |
|`429`   | Too many requests                 |
|`500`   | Internal server error             |

### Protocol

All the traffic should be either `h2` or `http/1.1`.

### Pagination

All `GET` method will return first 20 entries by default, use
`?at=x&limit=y` to specify skipping `x` entries and returning `y`
entries.

### Error Handling

Except for `2xx` or `5xx`, the server may return a json with a list of
reasons.

```json
Content-Type: application/json

{
    "reasons": [String]
}
```

#### GET `/v0/ping`

The server returns `HTTP 418` with a `pong` message.


## User Authentication

#### POST `/v0/user/login`

```json
Content-Type: application/json

{
    "username": String,
    "password": String
}
```

##### 200 OK

```
Set-Cookie: ecsession=Token; Max-Age=Int; Domain=String; Secure
```

##### 401 Unauthorized


#### POST `/v0/user/logout`

##### 200 OK

##### 401 Unauthorized


## Folder

#### GET `/v0/folder/:folder?sorted=`

`sorted` option is a string with the first letter of each field, which
comes first will have a higher priority:

|Field      |
|-----------|
|`Title`    |
|`Datetime` |
|`Flagged`  |
|`IsRead`   |
|`Sender`   |
|`Priority` |

For example, `fdi`, flagged email will be sorted at the top, then sort
by datetime, and lastly whether it is read.

##### 200 OK

```json
Set-Cookie: ecsession=Token; Max-Age=Int; Domain=String; Secure
Content-Type: application/json

[
    {
        "id": Int,
        "subject": String,
        "from": EmailString,
        "time": Datetime,
        "flagged": bool,
        "answered": bool,
        "seen": bool,
        "priority": OneOf[1, 2, 3, 4, 5],
        "preview": Optional[EncodedString]
    }, {...}
]
```

##### 400 Bad Request

##### 404 Not Found

##### 429 Too many requests

#### POST `/v0/folder/:folder`

##### 201 Created

##### 401 Unauthorized

##### 409 Conflict

#### PUT `/v0/folder/:oldFolder`

```json
Content-Type: application/json

{
    "as": String
}
```

##### 202 Processed

##### 404 Not Found

##### 409 Conflict

#### DELETE `/v0/folder/:folder`

##### 202 Processed

##### 403 Forbidden

##### 404 Not Found

## Email

#### GET `/v0/email/:emailID`

##### 200 OK

```json
Content-Type: application/json

{
    "date": Datetime,
    "from": EmailString,
    "to": [EmailString],
    "cc": [EmailString],
    "bcc": [EmailString],
    "reply_to": [EmailString],
    "priority": OneOf[1, 2, 3, 4, 5],
    "subject": String,
    "flagged": bool,
    "answered": bool,
    "seen": bool,
    "mime": String,
    "thread": [EmailID],
    "folder": Folder,
    "content": EncodedString,
    "attachments": [EncodedString]
}
```

##### 404 Not Found

#### POST `/v0/email`

```json
Content-Type: application/json

{
    "date": Datetime,
    "from": EmailString,
    "to": [EmailString],
    "cc": [EmailString],
    "bcc": [EmailString],
    "reply_to": [EmailString],
    "priority": OneOf[1, 2, 3, 4, 5],
    "subject": String,
    "flagged": bool,
    "answered": bool,
    "seen": bool,
    "mime": String,
    "thread": [EmailID],
    "folder": Folder,
    "content": EncodedString,
    "attachments": [EncodedString]
}
```

##### 201 Created

```json
Set-Cookie: ecsession=Token; Max-Age=Int; Domain=String; Secure
Content-Type: application/json

{
    "id": EmailID
}
```

##### 400 Bad Request

```json
Content-Type: application/json

{
    "reasons": [String]
}
```

##### 429 Too many requests

#### PATCH `/v0/email/:emailID`

```json
Content-Type: application/json

Any {
    "date": Datetime,
    "from": EmailString,
    "to": [EmailString],
    "cc": [EmailString],
    "bcc": [EmailString],
    "reply_to": [EmailString],
    "priority": OneOf[1, 2, 3, 4, 5],
    "subject": String,
    "flagged": bool,
    "answered": bool,
    "seen": bool,
    "mime": String,
    "thread": [EmailID],
    "folder": Folder,
    "content": EncodedString,
    "attachments": [EncodedString]
}
```

##### 202 Processed

##### 400 Bad Request

```json
Content-Type: application/json

{
    "reasons": [String]
}
```

##### 403 Forbidden

The user should not modify the email it self, except for fields with
`bool`.

#### DELETE `/v0/email/:emailID`

##### 202 Processed

##### 404 Not Found

