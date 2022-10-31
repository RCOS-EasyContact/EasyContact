package app.easycontact.server.imap;

public enum EmailReceiverProtocol {
    IMAP("imap"), POP3("pop3");
    private final String enumText;

    EmailReceiverProtocol(final String enumText) {
        this.enumText = enumText;
    }

    @Override
    public String toString() {
        return this.enumText;
    }
}
