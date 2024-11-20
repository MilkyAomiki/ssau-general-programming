import java.util.Random;

import functions.Functions;
import functions.basic.Log;
import functions.threads.Task;

public class Program {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_BLACK = "\u001B[30m";
    public static final String ANSI_RED = "\u001B[31m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_YELLOW = "\u001B[33m";
    public static final String ANSI_BLUE = "\u001b[34;40;1m";
    public static final String ANSI_PURPLE = "\u001B[35m";
    public static final String ANSI_CYAN = "\u001B[36m";
    public static final String ANSI_MAGENTA = "\u001b[35;40;1m";
    public static final String ANSI_WHITE = "\u001B[37m";

    public static void main(String[] args) {
        nonThread();
    }

    public static void nonThread() {
        Task task = new Task();
        task.setTaskCount(100);

        for (int i = 0; i < task.getTaskCount(); i++) {


            task.setFunc(new Log(1 + 9*Math.random()));
            task.setLeftLim(100*Math.random());
            task.setRightLim(100 + 100*Math.random());
            task.setIntegrationStep(Math.random());
            
            System.out.println(ANSI_BLUE + "Source " + ANSI_RESET + task.getLeftLim() + " " + task.getRightLim() + " " + task.getIntegrationStep());

            double integral = Functions.integrate(task.getFunc(), task.getLeftLim(), task.getRightLim(), task.getIntegrationStep());

            System.out.println(ANSI_GREEN + "Result " + ANSI_RESET + task.getLeftLim() + " " + task.getRightLim() + " " + task.getIntegrationStep() + " " + integral);
        }
    }
}
