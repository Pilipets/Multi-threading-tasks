package simulator;

import javax.swing.*;
import java.applet.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ControlPanel extends Frame
{
    Kernel kernel ;
    JButton runButton = new JButton("run");
    JButton stepButton = new JButton("step");
    JButton resetButton = new JButton("reset");
    JButton exitButton = new JButton("exit");
    final int pagesAmount = 64;
    JButton[] buttons = new JButton[pagesAmount];
    Label[] labels = new Label[pagesAmount];

    Label statusValueLabel = new Label("STOP" , Label.LEFT) ;
    Label timeValueLabel = new Label("0" , Label.LEFT) ;
    Label instructionValueLabel = new Label("NONE" , Label.LEFT) ;
    Label addressValueLabel = new Label("NULL" , Label.LEFT) ;
    Label pageFaultValueLabel = new Label("NO" , Label.LEFT) ;
    Label virtualPageValueLabel = new Label("x" , Label.LEFT) ;
    Label physicalPageValueLabel = new Label("0" , Label.LEFT) ;
    Label RValueLabel = new Label("0" , Label.LEFT) ;
    Label MValueLabel = new Label("0" , Label.LEFT) ;
    Label inMemTimeValueLabel = new Label("0" , Label.LEFT) ;
    Label lastTouchTimeValueLabel = new Label("0" , Label.LEFT) ;
    Label lowValueLabel = new Label("0" , Label.LEFT) ;
    Label highValueLabel = new Label("0" , Label.LEFT) ;


    public ControlPanel( String title )
    {
        super(title);
        for(int i = 0; i < pagesAmount; ++i) {
            buttons[i] = new JButton("p"+i);
            int finalI = i;
            buttons[i].addActionListener(actionEvent -> kernel.getPage(finalI));
            labels[i] = new Label(null,Label.CENTER);
            labels[i].setText(null);
            labels[i].setAlignment(Label.CENTER);

        }
    }

    public void init( Kernel useKernel , String commands , String config )
    {
        kernel = useKernel ;
        kernel.setControlPanel( this );
        setLayout( null );
        setBackground( Color.white );
        setForeground( Color.black );
        setSize( 635 , 545 );
        setFont( new Font( "Courier", Font.PLAIN, 12 ) );

        runButton.setForeground( Color.blue );
        runButton.setBackground( Color.lightGray );
        runButton.setBounds( 0,30,70,15 );
        runButton.addActionListener(actionEvent -> {
            setStatus( "RUN" );
            runButton.setEnabled(false);
            stepButton.setEnabled(false);
            resetButton.setEnabled(false);
            kernel.run();
            setStatus( "STOP" );
            resetButton.setEnabled(true);
        });
        add( runButton );

        stepButton.setForeground( Color.blue );
        stepButton.setBackground( Color.lightGray );
        stepButton.setBounds( 70,30,70,15 );
        stepButton.addActionListener(actionEvent -> {
            setStatus( "STEP" );
            kernel.step();
            if (kernel.runcycles == kernel.runs) {
                stepButton.setEnabled(false);
                runButton.setEnabled(false);
            }
            setStatus("STOP");
        });
        add( stepButton );

        resetButton.setForeground( Color.blue );
        resetButton.setBackground( Color.lightGray );
        resetButton.setBounds( 140,30,70,15 );
        resetButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                kernel.reset();
                runButton.setEnabled(true);
                stepButton.setEnabled(true);
            }
        });
        add( resetButton );

        exitButton.setForeground( Color.blue );
        exitButton.setBackground( Color.lightGray );
        exitButton.setBounds( 210,30,70,15 );
        exitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                System.exit(0);
            }
        });
        add( exitButton );

        for(int i = 0; i < pagesAmount; ++i) {
            buttons[i].setBounds(140*(i/32), (i%32+2)*15+25, 70, 15);
            buttons[i].setForeground( Color.magenta );
            buttons[i].setBackground( Color.lightGray );
            add ( buttons[i] );

            labels[i].setBounds( 70+140*(i/32), (i%32+2)*15+25, 60, 15 );
            labels[i].setForeground( Color.red );
            labels[i].setFont( new Font( "Courier", Font.PLAIN, 10 ) );
            add( labels[i] );
        }


        statusValueLabel.setBounds( 345,0+25,100,15 );
        add( statusValueLabel );

        timeValueLabel.setBounds( 345,15+25,100,15 );
        add( timeValueLabel );

        instructionValueLabel.setBounds( 385,45+25,100,15 );
        add( instructionValueLabel );

        addressValueLabel.setBounds(385,60+25,230,15);
        add( addressValueLabel );

        pageFaultValueLabel.setBounds( 385,90+25,100,15 );
        add( pageFaultValueLabel );

        virtualPageValueLabel.setBounds( 395,120+25,200,15 );
        add( virtualPageValueLabel );

        physicalPageValueLabel.setBounds( 395,135+25,200,15 );
        add( physicalPageValueLabel );

        RValueLabel.setBounds( 395,150+25,200,15 );
        add( RValueLabel );

        MValueLabel.setBounds( 395,165+25,200,15 );
        add( MValueLabel );

        inMemTimeValueLabel.setBounds(395,180+25,200,15 );
        add( inMemTimeValueLabel );

        lastTouchTimeValueLabel.setBounds( 395,195+25,200,15 );
        add( lastTouchTimeValueLabel );

        lowValueLabel.setBounds( 395,210+25,230,15 );
        add( lowValueLabel );

        highValueLabel.setBounds( 395,225+25,230,15 );
        add( highValueLabel );

        Label virtualOneLabel = new Label( "virtual" , Label.CENTER) ;
        virtualOneLabel.setBounds(0,15+25,70,15);
        add(virtualOneLabel);

        Label virtualTwoLabel = new Label( "virtual" , Label.CENTER) ;
        virtualTwoLabel.setBounds(140,15+25,70,15);
        add(virtualTwoLabel);

        Label physicalOneLabel = new Label( "physical" , Label.CENTER) ;
        physicalOneLabel.setBounds(70,15+25,70,15);
        add(physicalOneLabel);

        Label physicalTwoLabel = new Label( "physical" , Label.CENTER) ;
        physicalTwoLabel.setBounds(210,15+25,70,15);
        add(physicalTwoLabel);

        Label statusLabel = new Label("status: " , Label.LEFT) ;
        statusLabel.setBounds(285,0+25,65,15);
        add(statusLabel);

        Label timeLabel = new Label("time: " , Label.LEFT) ;
        timeLabel.setBounds(285,15+25,50,15);
        add(timeLabel);

        Label instructionLabel = new Label("instruction: " , Label.LEFT) ;
        instructionLabel.setBounds(285,45+25,100,15);
        add(instructionLabel);

        Label addressLabel = new Label("address: " , Label.LEFT) ;
        addressLabel.setBounds(285,60+25,85,15);
        add(addressLabel);

        Label pageFaultLabel = new Label("page fault: " , Label.LEFT) ;
        pageFaultLabel.setBounds(285,90+25,100,15);
        add(pageFaultLabel);

        Label virtualPageLabel = new Label("virtual page: " , Label.LEFT) ;
        virtualPageLabel.setBounds(285,120+25,110,15);
        add(virtualPageLabel);

        Label physicalPageLabel = new Label("physical page: " , Label.LEFT) ;
        physicalPageLabel.setBounds(285,135+25,110,15);
        add(physicalPageLabel);

        Label RLabel = new Label("R: ", Label.LEFT) ;
        RLabel.setBounds(285,150+25,110,15);
        add(RLabel);

        Label MLabel = new Label("M: " , Label.LEFT) ;
        MLabel.setBounds(285,165+25,110,15);
        add(MLabel);

        Label inMemTimeLabel = new Label("inMemTime: " , Label.LEFT) ;
        inMemTimeLabel.setBounds(285,180+25,110,15);
        add(inMemTimeLabel);

        Label lastTouchTimeLabel = new Label("lastTouchTime: " , Label.LEFT) ;
        lastTouchTimeLabel.setBounds(285,195+25,110,15);
        add(lastTouchTimeLabel);

        Label lowLabel = new Label("low: " , Label.LEFT) ;
        lowLabel.setBounds(285,210+25,110,15);
        add(lowLabel);

        Label highLabel = new Label("high: " , Label.LEFT) ;
        highLabel.setBounds(285,225+25,110,15);
        add(highLabel);

        kernel.init( commands , config );

        setVisible(true);
    }

    public void paintPage( Page page )
    {
        virtualPageValueLabel.setText( Integer.toString( page.id ) );
        physicalPageValueLabel.setText( Integer.toString( page.physical ) );
        RValueLabel.setText( Integer.toString( page.R ) );
        MValueLabel.setText( Integer.toString( page.M ) );
        inMemTimeValueLabel.setText( Integer.toString( page.inMemTime ) );
        lastTouchTimeValueLabel.setText( Integer.toString( page.lastTouchTime ) );
        lowValueLabel.setText(Long.toString( page.low , Kernel.addressradix ) );
        highValueLabel.setText(Long.toString( page.high , Kernel.addressradix ) );
    }

    public void setStatus(String status) {
        statusValueLabel.setText(status);
    }

    public void addPhysicalPage( int pageNum , int physicalPage )
    {
        if(physicalPage < 0 || physicalPage > 63) {
            return;
        }
        labels[physicalPage].setText("page " + pageNum);
    }

    public void removePhysicalPage( int physicalPage )
    {
        if(physicalPage < 0 || physicalPage > 63) {
            return;
        }
        labels[physicalPage].setText(null);
    }
}
