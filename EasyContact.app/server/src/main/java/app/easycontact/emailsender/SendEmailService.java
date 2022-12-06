package app.easycontact.emailsender;

public interface SendEmailService {
    void sendSimpleMessage(String from, String to, String subject, String text);
}
