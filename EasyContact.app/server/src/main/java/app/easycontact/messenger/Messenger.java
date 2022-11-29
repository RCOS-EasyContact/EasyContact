package app.easycontact.messenger;

public interface Messenger {

    void send(String to, String title, String text);

    void receive();

}
