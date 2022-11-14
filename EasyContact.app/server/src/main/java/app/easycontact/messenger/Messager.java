package app.easycontact.messenger;

public interface Messager {

    void send(String to, String title, String text);

    void receive();

}
