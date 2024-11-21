import functions.Functions;
import functions.basic.Log;
import functions.threads.Generator;
import functions.threads.Integrator;
import functions.threads.Sem;
import functions.threads.SimpleGenerator;
import functions.threads.SimpleIntegrator;
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
        //complicatedThreads();
        simpleThreads();
        //nonThread();
    }

    public static void simpleThreads() {
        Task task = new Task(100);
        Thread threadGen = new Thread(new SimpleGenerator(task), "Generator thread");
        Thread threadInt = new Thread(new SimpleIntegrator(task), "Integrator thread");

        threadGen.setPriority(Thread.MAX_PRIORITY);
        threadInt.setPriority(Thread.MIN_PRIORITY);
        threadGen.start();
        threadInt.start();
    }

    public static void complicatedThreads() {
        Task task = new Task(100);
        Sem sem = new Sem();

        Thread threadGen = new Generator(task, sem);
        Thread threadInt = new Integrator(task, sem);

        //threadGen.setPriority(Thread.MIN_PRIORITY);
        //threadInt.setPriority(Thread.MAX_PRIORITY);
        threadGen.start();
        threadInt.start();

        try {
            Thread.sleep(20);
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        threadGen.interrupt();
        threadInt.interrupt();
    }

    public static void nonThread() {
        Task task = new Task(100);

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
