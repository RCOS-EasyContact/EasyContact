package app.easycontact.server.imap;

import lombok.NonNull;
import lombok.experimental.SuperBuilder;

@SuperBuilder
public abstract class EmailReceiver {
    @NonNull String userName;
    @NonNull String userPassword;
    @NonNull String serverName;
    @NonNull String serverPort;

    /**
     * Downloads new messages and fetches details for each message.
     *
     * @param folder name of the email folder
     */
    public abstract void downloadEmails(String folder);
}
