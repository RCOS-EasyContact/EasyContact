package app.easycontact.emailsender;

public interface SendEmailService {
    void sendSimpleMessage(String to, String subject, String text);
}
