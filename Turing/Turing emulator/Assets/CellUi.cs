using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class CellUi : MonoBehaviour
{
    public TMPro.TMP_InputField s_i;
    public TMPro.TMP_InputField st_i;
    public TMPro.TextMeshProUGUI button_t;
    int state = 0;
    public void onButton() {
        if (state == 0) {
            state = 1;
            button_t.SetText(">");
        } else if (state == 1) {
            state = -1;
            button_t.SetText("<");
        } else if (state == -1) {
            state = 0;
            button_t.SetText("=");
        }
    }
    public int getState() {
        try {
            return int.Parse(st_i.text);
        }
        catch (System.Exception) {
            return 0;
        }
        
    }
    public string getSymbol() {
        return s_i.text;
    }
    public int getAct() {
        return state;
    }
}
