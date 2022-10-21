package app.easycontact.emailsender;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.core.env.Environment;
import org.springframework.mail.javamail.JavaMailSender;
import org.springframework.mail.javamail.JavaMailSenderImpl;

import java.util.Properties;

@Configuration
public class MailSenderConfig {
    private final Environment env;

    //    private String host;
    @Autowired
    public MailSenderConfig(Environment env) {
        this.env = env;
    }

    @Bean
    public JavaMailSender getJavaMailSender() {
        JavaMailSenderImpl mailSender = new JavaMailSenderImpl();
        mailSender.setHost(env.getProperty("easycontact.email.host"));
        mailSender.setPort(587);
        mailSender.setUsername(env.getProperty("easycontact.email.username"));
        mailSender.setPassword(env.getProperty("easycontact.email.password"));

        Properties props = mailSender.getJavaMailProperties();
        props.put("mail.transport.protocol", "smtp");
        props.put("mail.smtp.auth", "true");
        props.put("mail.smtp.starttls.enable", "true");
        props.put("mail.debug", env.getProperty("easycontact.email.debug", "false"));

        return mailSender;
    }
}
