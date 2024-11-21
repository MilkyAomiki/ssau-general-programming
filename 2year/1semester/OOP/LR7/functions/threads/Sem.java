package functions.threads;

public class Sem {
    private boolean isReadReady = false;
    public void acquireWrite() throws InterruptedException
    {
        if (isReadReady) {
            wait();
        }
    }

    public void releaseWrite() throws InterruptedException
    {
        notifyAll();
        isReadReady = true;
        if (Thread.interrupted()) {
            throw new InterruptedException();
        }
    }

    public void acquireRead() throws InterruptedException
    {
        if (!isReadReady) {
            wait();
        }
    }

    public void releaseRead() throws InterruptedException
    {
        notifyAll();
        isReadReady = false;
        if (Thread.interrupted()) {
            throw new InterruptedException();
        }
    }
}
