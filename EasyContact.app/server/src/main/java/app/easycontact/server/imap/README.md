# EasyContact IMAP Client

- Package `app.easycontact.server.imap`

## Usage

- Create an `EmailReceiver` instance using `EmailReceiverImplementation.builder()`
  - `serverName`: IMAP server's domain name
  - `serverPort`: IMAP server's port
  - `userName`: Username used for authentication
  - `userPassword`: Password used for authentication

  ```java
  EmailReceiver emailReceiver = EmailReceiverImplementation.builder()
                                                           .serverName("mail.rpi.edu")
                                                           .serverPort("993")
                                                           .userName("rcsid")
                                                           .userPassword("password")
                                                           .build();
  ```

- Download emails from `INBOX` folder

    ```java
    emailReceiver.downloadEmails("INBOX");
    ```
