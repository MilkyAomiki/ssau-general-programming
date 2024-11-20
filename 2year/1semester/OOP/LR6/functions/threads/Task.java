package functions.threads;

import functions.Function;

public class Task {
    public Task(int taskCount) {
        this.taskCount = taskCount;
    }

    public Boolean isGenerated = false;
    private Function func;
    private double leftLim;
    private double rightLim;
    private double integrationStep;
    
    private int taskCount;

    public Function getFunc() {
        return func;
    }

    public void setFunc(Function func) {
        this.func = func;
    }

    public double getLeftLim() {
        return leftLim;
    }

    public void setLeftLim(double leftLim) {
        this.leftLim = leftLim;
    }

    public double getRightLim() {
        return rightLim;
    }

    public void setRightLim(double rightLim) {
        this.rightLim = rightLim;
    }

    public double getIntegrationStep() {
        return integrationStep;
    }

    public void setIntegrationStep(double integrationStep) {
        this.integrationStep = integrationStep;
    }

    public int getTaskCount() {
        return taskCount;
    }
}
