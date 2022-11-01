package app.easycontact.server.imap;

import lombok.Data;
import lombok.experimental.SuperBuilder;

@SuperBuilder
@Data
public abstract class Email {
    public final long id;
    public final String from;
    public final String subject;
    public final String toList;
    public final String ccList;
    public final String sendDate;
    public final String message;
}
