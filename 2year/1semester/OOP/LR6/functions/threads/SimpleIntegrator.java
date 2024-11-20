package functions.threads;

import functions.Function;
import functions.Functions;

public class SimpleIntegrator implements Runnable {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_GREEN = "\u001B[32m";

    private Task task;
    
    public SimpleIntegrator(Task task) {
        this.task = task;
    }

    @Override
    public void run() {
        for (int i = 0; i < task.getTaskCount(); i++) {
            Function func;
            double leftLim;
            double rightLim;
            double integrationStep;

            synchronized (task)
            {
                if (!task.isGenerated) {
                    try {
                        task.wait();
                    } catch (InterruptedException e) {
                        // TODO Auto-generated catch block
                        e.printStackTrace();
                    }
                }

                //System.out.println(ANSI_GREEN + "READING DATA " + ANSI_RESET + i);

                func = task.getFunc();
                leftLim = task.getLeftLim();
                rightLim = task.getRightLim();
                integrationStep = task.getIntegrationStep();

                //System.out.println(ANSI_GREEN + "DATA READ" + ANSI_RESET + i);

                task.isGenerated = false;
                task.notifyAll();


                //System.out.println(ANSI_GREEN + "INTEGRATING DATA " + ANSI_RESET + i);

            }

            double integral = Functions.integrate(func, leftLim, rightLim, integrationStep);
            System.out.println(ANSI_GREEN + "Result " + ANSI_RESET + leftLim + " " + rightLim + " " + integrationStep + " " + integral);
        }
    }
    
}
