package app.easycontact.emailsender;

import app.easycontact.server.Application;
import graphql.ExecutionResult;
import graphql.GraphQL;
import graphql.schema.GraphQLSchema;
import graphql.schema.StaticDataFetcher;
import graphql.schema.idl.RuntimeWiring;
import graphql.schema.idl.SchemaGenerator;
import graphql.schema.idl.SchemaParser;
import graphql.schema.idl.TypeDefinitionRegistry;
import lombok.extern.log4j.Log4j2;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.core.env.Environment;
import org.springframework.test.context.ActiveProfiles;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.web.util.UriComponentsBuilder;

import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Date;

import static graphql.schema.idl.RuntimeWiring.newRuntimeWiring;

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

    private boolean verifyEmailGraphQL() {
        String schema = "type Query{hello: String}";

        SchemaParser schemaParser = new SchemaParser();
        TypeDefinitionRegistry typeDefinitionRegistry = schemaParser.parse(schema);

        RuntimeWiring runtimeWiring = newRuntimeWiring()
                .type("Query", builder -> builder.dataFetcher("hello", new StaticDataFetcher("world")))
                .build();

        SchemaGenerator schemaGenerator = new SchemaGenerator();
        GraphQLSchema graphQLSchema = schemaGenerator.makeExecutableSchema(typeDefinitionRegistry, runtimeWiring);

        GraphQL build = GraphQL.newGraphQL(graphQLSchema).build();
        ExecutionResult executionResult = build.execute("{hello}");

        System.out.println(executionResult.getData().toString());
        // Prints: {hello=world}
        return true;
    }

    @Test
    void verifyEmailJson() throws IOException {
        final String userAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:107.0) Gecko/20100101 Firefox/107.0";
        final String targetURL = "https://api.testmail.app/api/json";
        final Date date = new Date();

        URL obj = UriComponentsBuilder.fromUriString(targetURL)
                .queryParam("apikey", env.getRequiredProperty("easycontact.testemail.apikey"))
                .queryParam("namespace", "ml47u")
                .queryParam("timestamp_from", String.valueOf(date.getTime()))
                .queryParam("livequery", "true")
                .build();
        HttpURLConnection httpURLConnection = (HttpURLConnection) obj.openConnection();
        httpURLConnection.setRequestMethod("GET");
        httpURLConnection.setRequestProperty("User-Agent", userAgent);
        int responseCode = httpURLConnection.getResponseCode();
        log.info("GET Response Code :: " + responseCode);
        assert responseCode == HttpURLConnection.HTTP_OK;
//        if (responseCode == HttpURLConnection.HTTP_OK) { // success

//            return true;
//            BufferedReader in = new BufferedReader(new InputStreamReader(httpURLConnection.getInputStream()));
//            String inputLine;
//            StringBuffer response = new StringBuffer();
//
//            while ((inputLine = in .readLine()) != null) {
//                response.append(inputLine);
//            } in .close();
//
//            // print result
//            System.out.println(response.toString());
//        } else {
//            return false;
//            System.out.println("GET request not worked");
    }
}
}