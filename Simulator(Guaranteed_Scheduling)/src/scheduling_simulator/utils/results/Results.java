package scheduling_simulator.utils.results;

public class Results extends BasicResults {
    public float avgwt = 0, avgtt = 0;
    public Results(String schedulingType, String schedulingName, int compuTime) {
        super(schedulingType, schedulingName, compuTime);
    }
}
