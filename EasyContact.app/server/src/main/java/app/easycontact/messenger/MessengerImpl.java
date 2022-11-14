package app.easycontact.messenger;

import app.easycontact.emailsender.SendEmailService;
import app.easycontact.emailsender.SendEmailServiceImpl;

public class MessengerImpl implements Messager {
    private SendEmailService sendEmailService;
//    private recvEmailService recvEmailService;

    private String username;
    // password will not be saved
    private String from;
    private String signature;

    MessengerImpl(String from) {
        this.sendEmailService = new SendEmailServiceImpl();
        this.from = from;
    }

    @Override
    public void send(String to, String title, String text) {
        sendEmailService.sendSimpleMessage(from, to, title, text);
    }

    @Override
    public void receive() {
        throw new RuntimeException("Method does not implement!");
    }
}
