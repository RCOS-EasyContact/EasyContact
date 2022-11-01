package app.easycontact.server.imap;

public class ExampleMain {
    public static void main(String[] args) {
        EmailReceiver emailReceiver = EmailReceiverImplementation.builder().serverName("mail.rpi.edu").serverPort("993").userName("gongz3").userPassword("DO7gTmQVDeTjHWfU").build();
        emailReceiver.downloadEmails("INBOX");
    }
}
