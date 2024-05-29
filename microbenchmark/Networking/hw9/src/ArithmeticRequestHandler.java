import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

/**
 * hw 9
 *
 * Get input from client to server and compute calculation
 *
 * @author Zheying Lu, lab03
 * @version July 22
 */

public final class ArithmeticRequestHandler implements Runnable {
    /**
     * The client socket of this request handler.
     */
    private Socket clientSocket; //handle connection requests

    /*
     * Error message constants.
     */

    private static final String ILLEGAL_NUM_ARGUMENTS_ERROR_MESSAGE; //error message for illegal number arguments

    private static final String ILLEGAL_OPERATION_NAME_ERROR_MESSAGE; //error message for wrong argument name

    private static final String ILLEGAL_FIRST_OPERAND_ERROR_MESSAGE; //error message for wrong first argument

    private static final String ILLEGAL_SECOND_OPERAND_ERROR_MESSAGE; //error message for wrong second argument

    static {
        ILLEGAL_NUM_ARGUMENTS_ERROR_MESSAGE = String.format("%s: requests must include an operation name, " +
                "and two operands all separated by spaces\n", ArithmeticProtocol.ILLEGAL_REQUEST);

        ILLEGAL_OPERATION_NAME_ERROR_MESSAGE = String.format("%s: the operation name must be part of the protocol\n",
                ArithmeticProtocol.ILLEGAL_REQUEST);

        ILLEGAL_FIRST_OPERAND_ERROR_MESSAGE = String.format("%s: the first operand must be a valid integer\n",
                ArithmeticProtocol.ILLEGAL_REQUEST);

        ILLEGAL_SECOND_OPERAND_ERROR_MESSAGE = String.format("%s: the second operand must be a valid integer\n",
                ArithmeticProtocol.ILLEGAL_REQUEST);
    } //static

    /**
     * Constructs a newly allocated {@code ArithmeticRequestHandler} object with the specified client socket.
     *
     * @param clientSocket the client socket of this request handler
     * @throws IllegalArgumentException if the {@code clientSocket} argument is {@code null}
     */
    public ArithmeticRequestHandler(Socket clientSocket) throws IllegalArgumentException {
        if (clientSocket == null) {
            throw new IllegalArgumentException("clientSocket argument is null");
        } else {
            this.clientSocket = clientSocket;

        } //end if
    } //ArithmeticRequestHandler

    /**
     * Communicates with the client, and processes their requests until they disconnect.
     */
    @Override
    public void run() {

        try {
            Scanner in = new Scanner(clientSocket.getInputStream()); //scanner to get user input
            PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true); //writer for output

            while (in.hasNextLine()) {
                String input = in.nextLine();
                String[] split = input.split(" ");
                if (split.length != 3) {
                    out.printf(ILLEGAL_NUM_ARGUMENTS_ERROR_MESSAGE);
                } else if (!split[0].equals("ADD") && !split[0].equals("SUBTRACT")
                        && !split[0].equals("MULTIPLY") && !split[0].equals("DIVIDE")
                ) {
                    out.printf(ILLEGAL_OPERATION_NAME_ERROR_MESSAGE);
                } else {
                    int check = 0;
                    if (split[1].charAt(0) == '-') {
                        for (int i = 1; i < split[1].length(); i++) {
                            if (!Character.isDigit(split[1].charAt(i))) {
                                out.printf(ILLEGAL_FIRST_OPERAND_ERROR_MESSAGE);
                                check = 1;
                                break;
                            }
                        }
                    } else {
                        for (int i = 0; i < split[1].length(); i++) {
                            if (!Character.isDigit(split[1].charAt(i))) {
                                out.printf(ILLEGAL_FIRST_OPERAND_ERROR_MESSAGE);
                                check = 1;
                                break;
                            }
                        }
                    } //end if

                    if (split[2].charAt(0) == '-') {
                        for (int i = 1; i < split[2].length(); i++) {
                            if (!Character.isDigit(split[2].charAt(i))) {
                                out.printf(ILLEGAL_SECOND_OPERAND_ERROR_MESSAGE);
                                check = 1;
                                break;
                            }
                        }
                    } else {
                        for (int i = 0; i < split[2].length(); i++) {
                            if (!Character.isDigit(split[2].charAt(i))) {
                                out.printf(ILLEGAL_SECOND_OPERAND_ERROR_MESSAGE);
                                check = 1;
                                break;
                            }
                        }
                    } //end if


                    if (check == 0) {
                        if (split[0].equals("ADD")) {
                            out.println(Integer.parseInt(split[1]) + Integer.parseInt(split[2]));
                        }
                        if (split[0].equals("SUBTRACT")) {
                            out.println(Integer.parseInt(split[1]) - Integer.parseInt(split[2]));
                        }
                        if (split[0].equals("MULTIPLY")) {
                            out.println(Integer.parseInt(split[1]) * Integer.parseInt(split[2]));
                        }
                        if (split[0].equals("DIVIDE")) {
                            out.println(Integer.parseInt(split[1]) / Integer.parseInt(split[2]));
                        }
                    } //end if

                }

            }
        } catch (IOException e) {
            e.printStackTrace();
        }


    } //run
}