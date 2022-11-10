package app.easycontact.server.imap;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;

public class EmailTest {
    final long id = 1;
    final String from = "from@example.com";
    final String toList = "to@example.com";
    final String ccList = "cc@example.com";
    final String subject = "Example Subject";
    final String sendDate = "Example Date";
    final String message = "Example Message";
    Email email;

    @BeforeEach
    void setUp() {
        email = EmailImplementation.builder().id(id).from(from).toList(toList).ccList(ccList).subject(subject).sendDate(sendDate).message(message).build();
    }

    @Test
    public void testCreateEmail() {
        assertNotNull(email);
    }

    @Test
    public void testGetId() {
        assertEquals(email.getId(), id);
    }

    @Test
    public void testGetFrom() {
        assertEquals(email.getFrom(), from);
    }

    @Test
    public void testGetSubject() {
        assertEquals(email.getSubject(), subject);
    }

    @Test
    public void testGetToList() {
        assertEquals(email.getToList(), toList);
    }

    @Test
    public void testGetCcList() {
        assertEquals(email.getCcList(), ccList);
    }

    @Test
    public void testGetSendDate() {
        assertEquals(email.getSendDate(), sendDate);
    }

    @Test
    public void testGetMessage() {
        assertEquals(email.getMessage(), message);
    }
}
