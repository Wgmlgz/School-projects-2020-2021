using System.Collections;
using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.Runtime.InteropServices;

public class TuringMachineGO : MonoBehaviour {
    public float update_time = 0.5f;
    public float cur_time = 0;

    // ui
    public Slider speed_slider;
    public TMPro.TextMeshProUGUI ips_t;
    public TMPro.TextMeshProUGUI total_iterations_t;
    public Toggle auto_t;
    public int total_iterations;
    float last_display_ips;
    float ips;
    int iterations = 0;
    public float update_ips_time = 0.5f;

    public GameObject blink;
    public Head head;
    public GameObject cell_example;
    public int min_x;
    List<GameObject> cells = new List<GameObject>();

    IntPtr tm_p;

    [DllImport("turing")]
    private static extern IntPtr init();
    [DllImport("turing")]
    private static extern IntPtr initBrainfuck();
    //[DllImport("turing")]
    //private static extern void run(IntPtr tm, byte[] buf);
    [DllImport("turing")]
    private static extern void safeIterate(IntPtr tm);
    [DllImport("turing")]
    private static extern void getStr(IntPtr tm, byte[] buf);

    private void Awake() {
        head.tm = this;
    }
    void Start() {
        //tm_p = init();
        tm_p = initBrainfuck();
        //byte[] buf = new byte[300];
        //run(t, buf);
        //Debug.Log(System.Text.Encoding.ASCII.GetString(buf));
    }
    GameObject createCell(int x) {
        Debug.Log(min_x.ToString() + " " + x.ToString());
        var tmp_cell = Instantiate(cell_example);
        var c = tmp_cell.GetComponent<Cell>();
        c.tm = this;
        c.x = x;
        //tmp_cell.transform.position = getPos(x);
        tmp_cell.GetComponent<Cell>().setText("~");
        return tmp_cell;
    }
    void addCellLeft() {
        var tmp_cell = createCell(min_x - 1);
        --min_x;
        cells.Insert(0, tmp_cell);
    }
    void addCellRight() {
        var tmp_cell = createCell(cells.Count + min_x);
        cells.Add(tmp_cell);
    }
    public void iterate() {
        safeIterate(tm_p);
        blink.SetActive(!blink.activeSelf);
    }

    void Update() {
        if (auto_t.isOn) {
            update_time = Mathf.Pow(speed_slider.value, 7f);
            for (cur_time += Time.deltaTime; cur_time > update_time; cur_time -= update_time) {
                iterate();
                ++iterations;
                ++total_iterations;
            }
            head.move_time = update_time;
        } else {
            head.move_time = 0.1f;
        }

        // ui update
        last_display_ips += Time.deltaTime;
        if (last_display_ips > update_ips_time) {
            ips_t.SetText((iterations / update_ips_time).ToString() + " i/s");
            last_display_ips = 0;
            iterations = 0;
            total_iterations_t.SetText(total_iterations.ToString() + " total iterations");
        }

        // machine update
        byte[] buf = new byte[10000];
        getStr(tm_p, buf);
        string str = System.Text.Encoding.ASCII.GetString(buf);
        //string str = "rrrr`a`b`c`d%";

        Debug.Log(str);

        int i = 0;
        string tmp = "";
        int pos, state;

        for (; str[i] != '&'; ++i) tmp += str[i];
        pos = int.Parse(tmp);
        ++i;

        for (tmp = ""; str[i] != '&'; ++i) tmp += str[i];
        state = int.Parse(tmp);
        ++i;

        head.moveTo(pos + min_x);
        head.setState(state);

        for (; str[i] == 'l'; ++i) addCellLeft();
        for (; str[i] == 'r'; ++i) addCellRight();


        var substrs = str.Split('`', '%');
        for (int n = 0; n < cells.Count; ++n) cells[n].GetComponent<Cell>().setText(substrs[n + 1]);
    }

    public Vector3 getPos(float x) {
        int size = 40;

        // liniar
        //x += size / 2;
        //var pos = Vector3.zero;
        //float x_mod = x % size;
        //if (x_mod < 0) x_mod = size + x_mod;
        //pos.x = (x_mod - size / 2) * 1.5f;
        //pos.z = (x / size - (x_mod / size)) * 4;
        //return pos;

        // spiral
        x += size / 2;
        var r = x * 0.15f;
        var pos = new Vector3(r, 0, 0);
        var c = 2 * Mathf.PI * r;
        var target_angle = 1;
        pos = Quaternion.AngleAxis(Mathf.Pow(x, 0.4f) * size * 10f, Vector3.up) * pos;
        return pos;
    }
}
