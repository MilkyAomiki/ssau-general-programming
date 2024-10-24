package functions;

import java.io.Externalizable;
import java.io.IOException;
import java.io.ObjectInput;
import java.io.ObjectOutput;

public class FunctionNode implements Externalizable {
    private FunctionNode next;
    private FunctionNode prev;

    private FunctionPoint data;

    public FunctionNode(FunctionNode next, FunctionNode prev, FunctionPoint data) {
        this.next = next;
        this.prev = prev;
        this.data = data;
    }

    public FunctionPoint getData() {
        return data;
    }

    public void setData(FunctionPoint data) {
        this.data = data;
    }

    public FunctionNode getPrev() {
        return prev;
    }

    public void setPrev(FunctionNode prev) {
        this.prev = prev;
    }

    public FunctionNode getNext() {
        return next;
    }

    public void setNext(FunctionNode next) {
        this.next = next;
    }

    @Override
    public void writeExternal(ObjectOutput out) throws IOException {
        out.writeObject(next);
        out.writeObject(prev);
        out.writeObject(data);
    }

    @Override
    public void readExternal(ObjectInput in) throws IOException, ClassNotFoundException {
        next = (FunctionNode)in.readObject();
        prev = (FunctionNode)in.readObject();
        data = (FunctionPoint)in.readObject();
    }
}
