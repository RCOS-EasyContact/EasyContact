package app.easycontact.emailsender;

import app.easycontact.server.Application;
import lombok.extern.log4j.Log4j2;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.core.env.Environment;
import org.springframework.test.context.ActiveProfiles;
import org.springframework.test.context.ContextConfiguration;

@SpringBootTest
@ContextConfiguration(classes = Application.class)
@Log4j2
@ActiveProfiles("dev")
class SendEmailServiceImplTest {
    @Autowired
    private SendEmailServiceImpl sendEmailService;
    @Autowired
    private Environment env;

    @Test
    void sendSimpleMessage() {
//        TODO: automatic email test, https://testmail.app/docs/#get-started
        String from = env.getRequiredProperty("easycontact.email.username");
        String to = env.getRequiredProperty("easycontact.email.to");
        log.info("Sending test email");
        sendEmailService.sendSimpleMessage(from, to, "testtest", "teststsetstetest");
    }
}