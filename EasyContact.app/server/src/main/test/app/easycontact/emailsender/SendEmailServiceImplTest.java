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

    private boolean verifyEmail() {
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
}