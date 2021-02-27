using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cell : MonoBehaviour {
    public TMPro.TextMeshProUGUI text;
    [HideInInspector] public TuringMachineGO tm;
    public int x;
    public void setText(string s) {
        text.SetText(s);
    }
    private void LateUpdate() {
        transform.position = tm.getPos(x);
    }
}
