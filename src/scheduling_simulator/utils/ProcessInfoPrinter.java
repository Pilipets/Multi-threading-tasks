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
            case Completed:
                out.print("completed... ");
            case Registered:
                out.print("registered... ");
        }
        out.println(String.format("(%d %d %d)",p.cputime, p.ioblocking, p.cpudone));
    }
}
