package GUI;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumnModel;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;
import javax.swing.border.LineBorder;
import java.io.File;

public class GUI extends JFrame {
    private JTextField textField1;
    private JTextField textField2;
    private JButton load_button;
    private JSlider slid;
    private JTable table;
    private JButton start_button;
    private JButton stop_button;
    private JButton toStart_button;
    private JButton toEnd_button;
    private JButton back_button;
    private JButton next_button;
    private JButton gen_Button;

    public GUI() {

        super("A-Star");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // МОЖНО УБРАТЬ!!!
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        int W = (int) screenSize.getWidth() / 2; // получить ширину экрана
        int H = (int) screenSize.getHeight() / 2; // получить высоту экрана
        this.setSize(W, H);
        this.setResizable(true);

        // Сетка
        GridBagLayout gridBagLayout = new GridBagLayout();
        // размеры сетки                        0    1   2    3    4   5
        this.getContentPane().setLayout(gridBagLayout);

        // лейбл с Heights
        JLabel input_label1 = new JLabel("Width:");
        input_label1.setFont(new Font("Tahoma", Font.BOLD, 11));
        input_label1.setForeground(Color.BLACK);
        GridBagConstraints gbc_input_label = new GridBagConstraints();
        // отступы
        gbc_input_label.insets = new Insets(0, 0, 5, 5);
        // прижаться к краю ячейки
        gbc_input_label.anchor = GridBagConstraints.EAST;
        // номер ячейки в сетке
        gbc_input_label.gridx = 0;
        gbc_input_label.gridy = 0;
        this.getContentPane().add(input_label1, gbc_input_label);
        // Поле Heights
        textField1 = new JTextField();
        textField1.setBackground(new Color(255, 240, 245));
        GridBagConstraints gbc_textField = new GridBagConstraints();
        gbc_textField.insets = new Insets(0, 0, 5, 5);
        gbc_textField.fill = GridBagConstraints.EAST;
        gbc_textField.gridx = 1;
        gbc_textField.gridy = 0;
        this.getContentPane().add(textField1, gbc_textField);
        textField1.setColumns(5);
        textField1.setText("5"); //base field size

        // лейбл с Widths
        JLabel input_label2 = new JLabel("Height:");
        input_label2.setFont(new Font("Tahoma", Font.BOLD, 11));
        input_label2.setForeground(Color.BLACK);
        GridBagConstraints gbc_input_label1 = new GridBagConstraints();
        // отступы
        gbc_input_label1.insets = new Insets(0, 0, 5, 5);
        // прижаться к краю ячейки
        gbc_input_label1.anchor = GridBagConstraints.WEST;
        // номер ячейки в сетке
        gbc_input_label1.gridx = 2;
        gbc_input_label1.gridy = 0;
        this.getContentPane().add(input_label2, gbc_input_label1);
        // Поле Widths
        textField2 = new JTextField();
        textField2.setBackground(new Color(255, 240, 245));
        GridBagConstraints gbc_textField1 = new GridBagConstraints();
        gbc_textField1.insets = new Insets(0, 0, 5, 5);
        gbc_textField1.anchor = GridBagConstraints.WEST;
        gbc_textField1.gridx = 3;
        gbc_textField1.gridy = 0;
        this.getContentPane().add(textField2, gbc_textField1);
        textField2.setColumns(5);
        textField2.setText("5"); //base field size

        /*Action listen"*/
        ActionListener textActList = new TextActionListener();
        textField1.addActionListener(textActList);
        textField2.addActionListener(textActList);


        // Слайдер
        slid = new JSlider(1, 4, 2);
        // рисуем галочки и пометки
        slid.setSnapToTicks(true);
        slid.setPaintTrack(true);

        slid.setPaintTicks(true);
        slid.setPaintLabels(true);
        // установить интервал
        slid.setMajorTickSpacing(1);

        GridBagConstraints  slid_gbc = new GridBagConstraints();
        slid_gbc.insets = new Insets(20, 0, 5, 5);
        slid_gbc.anchor = GridBagConstraints.NORTH;
        slid_gbc.gridx = 3;
        slid_gbc.gridy = 0;
        this.getContentPane().add(slid, slid_gbc);

        // Выпадающий список
        JComboBox<String> comboBox = new JComboBox<>();
        comboBox.addItem("W");
        comboBox.addItem(" ");
        comboBox.addItem("S");
        comboBox.addItem("E");

        // Таблица
        table = new JTable();
        table.setRowSelectionAllowed(false);
        table.setBorder(new LineBorder(new Color(0, 0, 0)));
        table.setBackground(new Color(255, 240, 245));
        table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
        table.setRowHeight(18);
        DefaultTableModel dtm = (DefaultTableModel) table.getModel();
        dtm.setColumnCount(10);
        dtm.setRowCount(10);
        TableColumnModel columnModel = table.getColumnModel();
        for (int i=0; i<table.getColumnCount(); ++i) {
            columnModel.getColumn(i).setPreferredWidth(18);
            columnModel.getColumn(i).setCellEditor(new DefaultCellEditor(comboBox));
        }

        GridBagConstraints gbc_table = new GridBagConstraints();
        gbc_table.gridheight = 13;
        gbc_table.gridwidth = 3;
        gbc_table.insets = new Insets(0, 0, 15, 5);
        gbc_table.gridx = 1;
        gbc_table.gridy = 1;
        gbc_table.weightx = 1.0f;
        gbc_table.weighty = 1.0f;
        this.getContentPane().add(table, gbc_table);


        JLabel instruction_label_1 = new JLabel("W - wall, S - start, E - Exit");
        instruction_label_1.setForeground(Color.BLACK);
        instruction_label_1.setFont(new Font("Tahoma", Font.BOLD, 11));
        GridBagConstraints gbc_instruction_label_1 = new GridBagConstraints();
        gbc_instruction_label_1.anchor = GridBagConstraints.WEST;
        gbc_instruction_label_1.insets = new Insets(0, 0, 5, 20);
        gbc_instruction_label_1.gridx = 4;
        gbc_instruction_label_1.gridy = 0;
        this.getContentPane().add(instruction_label_1, gbc_instruction_label_1);

        // Файл
        load_button = new JButton("Load");
        load_button.setFont(new Font("Tahoma", Font.BOLD, 11));
        load_button.setBackground(new Color(255, 240, 245));
        GridBagConstraints gbc_load_Button = new GridBagConstraints();
        gbc_load_Button.insets = new Insets(0, 0, 5, 0);
        gbc_load_Button.gridx = 4;
        gbc_load_Button.gridy = 1;
        this.getContentPane().add(load_button, gbc_load_Button);
        /*Action listen"*/
        ActionListener buttonLoadActList = new ButtonLoadActionListener();
        load_button.addActionListener(buttonLoadActList);

        gen_Button = new JButton("Generate");
        gen_Button.setFont(new Font("Tahoma", Font.BOLD, 11));
        gen_Button.setBackground(new Color(255, 240, 245));
        GridBagConstraints gbc_gen_Button = new GridBagConstraints();
        gbc_gen_Button.insets = new Insets(0, 0, 5, 0);
        gbc_gen_Button.gridx = 4;
        gbc_gen_Button.gridy = 2;
        this.getContentPane().add(gen_Button, gbc_gen_Button);
        /*Action listen"*/
        ActionListener buttonGenerateActList = new ButtonGenerateActionListener();
        gen_Button.addActionListener(buttonGenerateActList);

        toStart_button = new JButton("ToStart");
        toStart_button.setFont(new Font("Tahoma", Font.BOLD, 11));
        toStart_button.setForeground(Color.BLACK);
        toStart_button.setBackground(new Color(255, 240, 245));
        GridBagConstraints gbc_toStart_button = new GridBagConstraints();
        gbc_toStart_button.insets = new Insets(0, 0, 5, 0);
        gbc_toStart_button.gridx = 4;
        gbc_toStart_button.gridy = 3;
        this.getContentPane().add(toStart_button, gbc_toStart_button);
        ActionListener buttonToStartActList = new ButtonToStartActionListener();
        toStart_button.addActionListener(buttonToStartActList);

        toEnd_button = new JButton("ToEnd");
        toEnd_button.setFont(new Font("Tahoma", Font.BOLD, 11));
        toEnd_button.setForeground(Color.BLACK);
        toEnd_button.setBackground(new Color(255, 240, 245));
        GridBagConstraints gbc_toEnd_button = new GridBagConstraints();
        gbc_toEnd_button.insets = new Insets(0, 0, 5, 0);
        gbc_toEnd_button.gridx = 4;
        gbc_toEnd_button.gridy = 4;
        this.getContentPane().add(toEnd_button, gbc_toEnd_button);
        /*Action listen"*/
        ActionListener buttonToEndActList = new ButtonToEndActionListener();
        toEnd_button.addActionListener(buttonToEndActList);

        back_button = new JButton("Back");
        back_button.setFont(new Font("Tahoma", Font.BOLD, 11));
        back_button.setForeground(Color.BLACK);
        back_button.setBackground(new Color(255, 240, 245));
        GridBagConstraints gbc_back_button = new GridBagConstraints();
        gbc_back_button.insets = new Insets(0, 0, 5, 0);
        gbc_back_button.gridx = 4;
        gbc_back_button.gridy = 5;
        this.getContentPane().add(back_button, gbc_back_button);
        ActionListener buttonBackActList = new ButtonBackActionListener();
        back_button.addActionListener(buttonBackActList);

        next_button = new JButton("Next");
        next_button.setFont(new Font("Tahoma", Font.BOLD, 11));
        next_button.setBackground(new Color(255, 240, 245));
        next_button.setForeground(Color.BLACK);
        GridBagConstraints gbc_next_button = new GridBagConstraints();
        gbc_next_button.insets = new Insets(0, 0, 5, 0);
        gbc_next_button.gridx = 4;
        gbc_next_button.gridy = 6;
        this.getContentPane().add(next_button, gbc_next_button);
        /*Action listen"*/
        ActionListener buttonNextActList = new ButtonNextActionListener();
        next_button.addActionListener(buttonNextActList);

        start_button = new JButton("Start");
        start_button.setFont(new Font("Tahoma", Font.BOLD, 11));
        start_button.setForeground(Color.BLACK);
        start_button.setBackground(new Color(255, 240, 245));
        GridBagConstraints gbc_start_button = new GridBagConstraints();
        gbc_start_button.gridx = 4;
        gbc_start_button.gridy = 7;
        this.getContentPane().add(start_button, gbc_start_button);
        /*Action listen"*/
        ActionListener buttonStartActList = new ButtonStartActionListener();
        start_button.addActionListener(buttonStartActList);

        stop_button = new JButton("Stop");
        stop_button.setFont(new Font("Tahoma", Font.BOLD, 11));
        stop_button.setForeground(Color.BLACK);
        stop_button.setBackground(new Color(255, 240, 245));
        GridBagConstraints gbc_stop_button = new GridBagConstraints();
        gbc_stop_button.gridx = 4;
        gbc_stop_button.gridy = 8;
        this.getContentPane().add(stop_button, gbc_stop_button);
        stop_button.setVisible(false);
        /*Action listen"*/
        ActionListener buttonStopActList = new ButtonStopActionListener();
        stop_button.addActionListener(buttonStopActList);

        JMenuBar menubar = new JMenuBar();
        this.setJMenuBar(menubar);
        JMenu help = new JMenu("Help");
        menubar.add(help);
        JMenuItem about = new JMenuItem("About");
        help.add(about);
        this.setVisible(true);
    }

    public class TextActionListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent evt) {
            String textX = textField1.getText();
            String textY = textField2.getText();
            textField1.selectAll();
            int x, y;
            try {
                x = Integer.parseInt(textX);
                y = Integer.parseInt(textY);
            }
            catch (NumberFormatException e) {
                JOptionPane.showInternalMessageDialog(null, "Error! Wrong number format.");
                return;
            }
            if (x < 2 || x > 30) {
                JOptionPane.showInternalMessageDialog(null, "Error! Enter size of the field in range [2, 30].");
                return;
            }
            DefaultTableModel dtm = (DefaultTableModel) table.getModel();
            dtm.setColumnCount(x);
            dtm.setRowCount(y);
            TableColumnModel columnModel = table.getColumnModel();
            for (int i = 0; i < table.getColumnCount(); ++i)
                columnModel.getColumn(i).setPreferredWidth(20);
        }
    }

    public class ButtonLoadActionListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            JFileChooser fileopen = new JFileChooser();
            int ret = fileopen.showDialog(null, "Открыть файл");
            if (ret == JFileChooser.APPROVE_OPTION) {

                File file = fileopen.getSelectedFile();
            }
        }
    }

    public class ButtonNextActionListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {

        }
    }

    public class ButtonBackActionListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {

        }
    }

    public class ButtonStartActionListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {

            stop_button.setVisible(true);
            start_button.setVisible(false);
            toStart_button.setVisible(false);
            toEnd_button.setVisible(false);
            back_button.setVisible(false);
            next_button.setVisible(false);
            gen_Button.setVisible(false);
            load_button.setVisible(false);
        }
    }

    public class ButtonToEndActionListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {

        }
    }

    public class ButtonToStartActionListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {

        }
    }

    public class ButtonStopActionListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {

            stop_button.setVisible(false);
            start_button.setVisible(true);
            toStart_button.setVisible(true);
            toEnd_button.setVisible(true);
            back_button.setVisible(true);
            next_button.setVisible(true);
            gen_Button.setVisible(true);
            load_button.setVisible(true);
        }
    }

    public class ButtonGenerateActionListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            int x, y, koef;
            Random random = new Random();
            x = random.nextInt(28) + 2;
            y = random.nextInt(28) + 2;
            textField1.setText(x + " " + y);

            DefaultTableModel dtm = (DefaultTableModel) table.getModel();
            dtm.setColumnCount(x);
            dtm.setRowCount(y);
            TableColumnModel columnModel = table.getColumnModel();
            for (int i=0; i<table.getColumnCount(); ++i)
                columnModel.getColumn(i).setPreferredWidth(15);


            for (int i=0; i<table.getRowCount(); i++) {
                for (int j=0; j<table.getColumnCount(); j++) {
                    koef = random.nextInt(5);
                    if (koef == 0) table.setValueAt("1", i, j);
                    else table.setValueAt("", i, j);
                }
            }

            int koord_xS, koord_yS;
            koord_xS = random.nextInt(x - 1) + 1; //gen 2 - x
            koord_yS = random.nextInt(y - 1) + 1; //gen 2 - y

            table.setValueAt("S", koord_yS, koord_xS);

            int koord_xE, koord_yE;

            koord_xE = random.nextInt(x - 1) + 1; //gen 2 - x
            koord_yE = random.nextInt(y - 1) + 1; //gen 2 - y

            while (koord_xS == koord_xE && koord_yS == koord_yE) {
                koord_xE = random.nextInt(x - 1) + 1; //gen 2 - x
                koord_yE = random.nextInt(y - 1) + 1; //gen 2 - y
            }

            table.setValueAt("E", koord_yE, koord_xE);

            for (int j=0; j<table.getColumnCount(); j++) {
                table.getColumnModel().getColumn(j).setCellRenderer(new MyRenderer());
                table.updateUI();
            }
        }
    }

}