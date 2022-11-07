package app.easycontact.server;

import app.easycontact.emailsender.SendEmailService;
import lombok.extern.log4j.Log4j2;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.ApplicationRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.core.env.Environment;

@SpringBootApplication
@ComponentScan(basePackages = "app.easycontact.emailsender")
@Log4j2
public class Application {

    @Autowired
    private SendEmailService emailsender;

    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
    }

    @Bean
    ApplicationRunner applicationRunner(Environment environment) {
        return args -> {
            log.info("send email test");
            String from = environment.getRequiredProperty("easycontact.email.username");
            emailsender.sendSimpleMessage(from, "xiaoshaoyc@gmail.com", "testtest", "teststsetstetest");
        };
    }

}
