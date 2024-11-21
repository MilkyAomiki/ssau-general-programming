package functions.threads;

import functions.basic.Log;

public class Generator extends Thread {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_BLUE = "\u001b[34;40;1m";

    private Task task;
    private Sem semaphore;
        
    public Generator(Task task, Sem semaphore) {
        this.task = task;
        this.semaphore = semaphore;
    }

    @Override
    public void run() {
        for (int i = 0; i < task.getTaskCount(); i++) {
    
            synchronized(semaphore)
            {
                try {
                    semaphore.acquireWrite();

                    //System.out.println(ANSI_BLUE + "SETTING DATA " + ANSI_RESET + i);

                    task.setFunc(new Log(1 + 9*Math.random()));
                    task.setLeftLim(100*Math.random());
                    task.setRightLim(100 + 100*Math.random());
                    task.setIntegrationStep(Math.random());

                    //System.out.println(ANSI_BLUE + "DATA SET" + ANSI_RESET + i);

                    semaphore.releaseWrite();
                } catch (InterruptedException e) {
                    return;
                }
            }
        
            System.out.println(ANSI_BLUE + "Source " + ANSI_RESET + task.getLeftLim() + " " + task.getRightLim() + " " + task.getIntegrationStep());

        }
        
    }
    
}
