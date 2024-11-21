package functions.threads;

import functions.Function;
import functions.Functions;

public class Integrator extends Thread {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_GREEN = "\u001B[32m";

    private Task task;
    private Sem semaphore;
        
    public Integrator(Task task, Sem semaphore) {
        this.task = task;
        this.semaphore = semaphore;
    }

    @Override
    public void run() {
        for (int i = 0; i < task.getTaskCount(); i++) {
            Function func;
            double leftLim;
            double rightLim;
            double integrationStep;

            synchronized(semaphore)
            {
                try {
                    semaphore.acquireRead();

                    //System.out.println(ANSI_GREEN + "READING DATA " + ANSI_RESET + i);

                    func = task.getFunc();
                    leftLim = task.getLeftLim();
                    rightLim = task.getRightLim();
                    integrationStep = task.getIntegrationStep();

                    //System.out.println(ANSI_GREEN + "DATA READ" + ANSI_RESET + i);

                    semaphore.releaseRead();
                } catch (InterruptedException e) {
                    return;
                }
            }

            //System.out.println(ANSI_GREEN + "INTEGRATING DATA " + ANSI_RESET + i);


            double integral = Functions.integrate(func, leftLim, rightLim, integrationStep);
            System.out.println(ANSI_GREEN + "Result " + ANSI_RESET + leftLim + " " + rightLim + " " + integrationStep + " " + integral);
        }
    }
    
}
