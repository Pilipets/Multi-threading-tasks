package scheduling_simulator.utils;

import java.io.PrintStream;

public class ProcessInfoPrinter {
    public enum Status{
        Completed, Registered, Blocked
    }
    public static void print(PrintStream out, sProcess p, Status s){
        out.print(String.format("Process: %d ",p.id));
        switch (s){
            case Blocked:
                out.print("I/O blocked... ");
                break;
            case Completed:
                out.print("completed... ");
                break;
            case Registered:
                out.print("registered... ");
                break;
        }
        out.println(String.format("(cpuTime=%d ioBlocking=%d cpuDone=%d ratio=%f)",
                p.cputime, p.ioblocking, p.cpudone, p.responseRatio));
    }
}
