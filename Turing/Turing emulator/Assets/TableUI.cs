using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class TableUI : MonoBehaviour {
    int x, y;
    public GameObject vline_e;
    public GameObject cell_e;

    public HorizontalLayoutGroup hl;
    public List<GameObject> cols = new List<GameObject>();
    public List<List<CellUi>> cells = new List<List<CellUi>>();

    public RectTransform content;
    public TMPro.TMP_InputField table;

    public void toSTR() {
        string s = "";
        int id = 0;
        foreach (var i in cells) {
            s += "\"";
            s += cols[id].GetComponent<CollSc>().f.text;
            s += "\"";
            foreach (var j in i) {
                s += ",";
                s += "\"" + j.getSymbol() + "\",";
                if (j.getAct() == 0) s += "=,";
                if (j.getAct() == 1) s += ">,";
                if (j.getAct() == -1) s += "<,";
                s += j.getState().ToString();
            }
            if (id != x) s += "\n";
            ++id;
        }
        Debug.Log(s);
        table.text = s;
    }

    public void addCol() {
        
        var tmp = Instantiate(vline_e, hl.transform);
        cells.Add(new List<CellUi>());
        for (int i = 0; i < y; ++i) {
            var tc = Instantiate(cell_e, tmp.GetComponent<CollSc>().da.transform);
            cells[x].Add(tc.GetComponent<CellUi>());
        }
        ++x;
        cols.Add(tmp);
        //  var tmpr = new Rect(0f, 0f, 100f, 100f);
        toSTR();
    }

    public void addLine() {
        ++y;
        int j = 0;
        foreach (var i in cols) {
            var tmp = Instantiate(cell_e, i.GetComponent<CollSc>().da.transform);
            var r = i.GetComponent<RectTransform>().rect;
            i.GetComponent<RectTransform>().rect.Set(r.x, r.y, r.width, x * 50);
            cells[j].Add(tmp.GetComponent<CellUi>());
            ++j;
        }
        
        
        toSTR();
    }
    private void Update() {
        content.sizeDelta = new Vector2(x * 100 - 1000, y * 40 + 35);
        toSTR();
    }
}
