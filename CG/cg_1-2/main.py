import wx
from wx import glcanvas
from OpenGL.GL import *
from math import sqrt


primitives = {'GL_POINTS': GL_POINTS,
              'GL_LINES': GL_LINES,
              'GL_LINE_STRIP': GL_LINE_STRIP,
              'GL_LINE_LOOP': GL_LINE_LOOP,
              'GL_TRIANGLES': GL_TRIANGLES,
              'GL_TRIANGLE_STRIP': GL_TRIANGLE_STRIP,
              'GL_TRIANGLE_FAN': GL_TRIANGLE_FAN,
              'GL_QUADS': GL_QUADS,
              'GL_QUAD_STRIP': GL_QUAD_STRIP,
              'GL_POLYGON': GL_POLYGON}
alphaType = {'GL_NEVER': GL_NEVER,
             'GL_LESS': GL_LESS,
             'GL_EQUAL': GL_EQUAL,
             'GL_LEQUAL': GL_LEQUAL,
             'GL_GREATER': GL_GREATER,
             'GL_NOTEQUAL': GL_NOTEQUAL,
             'GL_GEQUAL': GL_GEQUAL,
             'GL_ALWAYS': GL_ALWAYS}
mixingSrc = {'GL_ZERO': GL_ZERO,
             'GL_ONE': GL_ONE,
             'GL_DST_COLOR': GL_DST_COLOR,
             'GL_ONE_MINUS_DST_COLOR': GL_ONE_MINUS_DST_COLOR,
             'GL_SRC_ALPHA': GL_SRC_ALPHA,
             'GL_ONE_MINUS_SRC_ALPHA': GL_ONE_MINUS_SRC_ALPHA,
             'GL_DST_ALPHA': GL_DST_ALPHA,
             'GL_ONE_MINUS_DST_ALPHA': GL_ONE_MINUS_DST_ALPHA,
             'GL_SRC_ALPHA_SATURATE': GL_SRC_ALPHA_SATURATE}
mixingDst = {'GL_ZERO': GL_ZERO,
             'GL_ONE': GL_ONE,
             'GL_SRC_COLOR': GL_SRC_COLOR,
             'GL_ONE_MINUS_SRC_COLOR': GL_ONE_MINUS_SRC_COLOR,
             'GL_SRC_ALPHA': GL_SRC_ALPHA,
             'GL_ONE_MINUS_SRC_ALPHA': GL_ONE_MINUS_SRC_ALPHA,
             'GL_DST_ALPHA': GL_DST_ALPHA,
             'GL_ONE_MINUS_DST_ALPHA': GL_ONE_MINUS_DST_ALPHA}


class Canvas(glcanvas.GLCanvas):
    def __init__(self, parent, id, attribList):
        super().__init__(parent, id=id, attribList=attribList)

        self.GLInitialized = False
        self.context = glcanvas.GLContext(self)
        self.SetCurrent(self.context)

        self.Bind(wx.EVT_SIZE, self.processSizeEvent)
        self.Bind(wx.EVT_PAINT, self.processPaintEvent)

        self.primitiveType = primitives[list(primitives.keys())[0]]
        self.secondDraw = False
        self.onClipping = [False, 0, 0]
        self.onTransparenting = [False, 100, alphaType[list(alphaType.keys())[0]], 100]
        self.onMixing = [False, mixingSrc[list(mixingSrc.keys())[0]], mixingDst[list(mixingDst.keys())[0]]]

    def processSizeEvent(self, event):
        (w, h) = self.GetClientSize()

        glViewport(0, 0, w, h)

        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1)

        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()

        self.Refresh(False)
        event.Skip()

    def processPaintEvent(self, event):
        if not self.GLInitialized:
            glClearColor(0.2, 0.2, 0.2, 1)
            self.GLInitialized = True
        self.OnDraw()
        event.Skip()

    def OnDraw(self):
        glClear(GL_COLOR_BUFFER_BIT)

        # Drawing here
        if self.onClipping[0]:
            self.GL_Clipping()
        h = self.GetClientSize().height
        self.GL_Drawing(0, h/8)
        if self.onTransparenting[0]:
            self.GL_Transparenting()
        if self.onMixing[0]:
            self.GL_Mixing()
        if self.secondDraw:
            self.GL_Drawing(0, -h/8, self.onTransparenting[1]/100)
        if self.onMixing[0]:
            self.GL_Mixing(False)
        if self.onTransparenting[0]:
            self.GL_Transparenting(False)
        if self.onClipping[0]:
            self.GL_Clipping(False)
        # End of drawing

        self.SwapBuffers()

    def GL_Drawing(self, x=0, y=0, alpha=1):
        w = self.GetClientSize().width
        vtx = [[-w/4, 0], [-w/8, w*sqrt(3)/8], [w/8, w*sqrt(3)/8], [w/4, 0], [w/8, -w*sqrt(3)/8], [-w/8, -w*sqrt(3)/8]]
        for i in vtx:
            i[0] += x
            i[1] += y

        glPointSize(2)
        glBegin(self.primitiveType)
        glColor4f(1, 0, 0, alpha)
        glVertex(vtx[0][0], vtx[0][1])
        glVertex(vtx[1][0], vtx[1][1])
        glColor4f(0, 1, 0, alpha)
        glVertex(vtx[2][0], vtx[2][1])
        glVertex(vtx[3][0], vtx[3][1])
        glColor4f(1, 1, 0, alpha)
        glVertex(vtx[4][0], vtx[4][1])
        glVertex(vtx[5][0], vtx[5][1])
        glEnd()

    def GL_Clipping(self, enable=True):
        if enable:
            (w, h) = self.GetClientSize()
            (x, y) = (int(w*self.onClipping[1]/100), int(h*self.onClipping[2]/100))
            glEnable(GL_SCISSOR_TEST)
            glScissor(x, y, w - x, h - y)
        else:
            glDisable(GL_SCISSOR_TEST)

    def GL_Transparenting(self, enable=True):
        if enable:
            glEnable(GL_ALPHA_TEST)
            glAlphaFunc(self.onTransparenting[2], self.onTransparenting[3]/100)
        else:
            glDisable(GL_ALPHA_TEST)

    def GL_Mixing(self, enable=True):
        if enable:
            glEnable(GL_BLEND)
            glBlendFunc(self.onMixing[1], self.onMixing[2])
        else:
            glDisable(GL_BLEND)


class L1Panel(wx.Panel):
    def __init__(self, parent, id):
        super().__init__(parent, id=id)

        s_flag = wx.EXPAND | (wx.ALL - wx.BOTTOM)
        choices = list(primitives.keys())
        self.m_primitive = wx.ComboBox(self, id=300, choices=choices, style=wx.CB_READONLY, value=choices[0])

        s = wx.GridBagSizer(5, 5)
        s.Add(wx.StaticText(self, label='Lab1'), pos=(0, 0), flag=s_flag, border=5)
        s.Add(wx.StaticText(self, label='примитив'), pos=(1, 0), flag=s_flag, border=5)
        s.Add(self.m_primitive, pos=(1, 1), flag=s_flag | wx.BOTTOM, border=5)

        s.AddGrowableCol(1)
        self.SetSizer(s)


class L2Panel(wx.Panel):
    def __init__(self, parent, id):
        super().__init__(parent, id=id)

        s_flag = wx.EXPAND | (wx.ALL - wx.BOTTOM)
        self.m_xPos_st = wx.StaticText(self, id=100, label='0 %')
        self.m_yPos_st = wx.StaticText(self, id=101, label='0 %')
        self.m_alpha_st = wx.StaticText(self, id=102, label='100 %')
        self.m_primitive_cb = wx.CheckBox(self, id=200)
        self.m_cutting_cb = wx.CheckBox(self, id=201)
        self.m_alpha_cb = wx.CheckBox(self, id=202)
        self.m_mixing_cb = wx.CheckBox(self, id=203)
        choices = list(alphaType.keys())
        self.m_alpha_cmb = wx.ComboBox(self, id=301, choices=choices, style=wx.CB_READONLY, value=choices[0])
        choices = list(mixingSrc.keys())
        self.m_mixingS_cmb = wx.ComboBox(self, id=302, choices=choices, style=wx.CB_READONLY, value=choices[0])
        choices = list(mixingDst.keys())
        self.m_mixingD_cmb = wx.ComboBox(self, id=303, choices=choices, style=wx.CB_READONLY, value=choices[0])
        self.m_xO_sl = wx.Slider(self, id=400)
        self.m_yO_sl = wx.Slider(self, id=401)
        self.m_alpha_sl = wx.Slider(self, id=402, value=100)
        self.m_alpha_sc = wx.SpinCtrl(self, id=500, value='100')

        s = wx.GridBagSizer(5, 5)
        s.Add(wx.StaticText(self, label='Lab2'), pos=(0, 0), flag=s_flag, border=5)
        s.Add(wx.StaticText(self, size=(130, 1)), pos=(0, 2), flag=s_flag, border=5)

        s.Add(wx.StaticText(self, label='второй примитив'), pos=(1, 0), span=(1, 3), flag=s_flag, border=5)
        s.Add(self.m_primitive_cb, pos=(1, 3), flag=s_flag | wx.ALIGN_RIGHT, border=5)

        s.Add(wx.StaticText(self, label='тест отсечения'), pos=(2, 0), span=(1, 3), flag=s_flag, border=5)
        s.Add(self.m_cutting_cb, pos=(2, 3), flag=s_flag | wx.ALIGN_RIGHT, border=5)

        s.Add(wx.StaticText(self, label='x'), pos=(3, 0), flag=s_flag, border=5)
        s.Add(self.m_xO_sl, pos=(3, 1), span=(1, 2), flag=s_flag, border=5)
        s.Add(self.m_xPos_st, pos=(3, 3), flag=s_flag, border=5)

        s.Add(wx.StaticText(self, label='y'), pos=(4, 0), flag=s_flag, border=5)
        s.Add(self.m_yO_sl, pos=(4, 1), span=(1, 2), flag=s_flag, border=5)
        s.Add(self.m_yPos_st, pos=(4, 3), flag=s_flag, border=5)

        s.Add(wx.StaticText(self, label='тест прозрачности'), pos=(5, 0), span=(1, 3), flag=s_flag, border=5)
        s.Add(self.m_alpha_cb, pos=(5, 3), flag=s_flag | wx.ALIGN_RIGHT, border=5)

        s.Add(self.m_alpha_cmb, pos=(6, 0), span=(1, 3), flag=s_flag, border=5)
        s.Add(self.m_alpha_sc, pos=(6, 3), flag=s_flag, border=5)
        s.Add(self.m_alpha_sl, pos=(7, 0), span=(1, 3), flag=s_flag, border=5)
        s.Add(self.m_alpha_st, pos=(7, 3), flag=s_flag, border=5)

        s.Add(wx.StaticText(self, label='тест смешения'), pos=(8, 0), span=(1, 3), flag=s_flag, border=5)
        s.Add(self.m_mixing_cb, pos=(8, 3), flag=s_flag | wx.ALIGN_RIGHT, border=5)

        s.Add(wx.StaticText(self, label='s factor'), pos=(9, 0), span=(1, 2), flag=s_flag, border=5)
        s.Add(self.m_mixingS_cmb, pos=(9, 2), span=(1, 2), flag=s_flag, border=5)

        s.Add(wx.StaticText(self, label='d factor'), span=(1, 2), pos=(10, 0), flag=s_flag, border=5)
        s.Add(self.m_mixingD_cmb, pos=(10, 2), span=(1, 2), flag=s_flag | wx.BOTTOM, border=5)

        self.SetSizer(s)


class MyFrame(wx.Frame):
    def __init__(self, parent, title):
        style = (wx.DEFAULT_FRAME_STYLE - wx.MAXIMIZE_BOX - wx.RESIZE_BORDER)
        super().__init__(parent, title=title, style=style, size=(700, 500))
        self.SetBackgroundColour((240, 240, 240))

        font = wx.SystemSettings.GetFont(wx.SYS_DEFAULT_GUI_FONT)
        font.SetPointSize(10)
        self.SetFont(font)

        self.m_lab1 = L1Panel(self, id=0)
        self.m_lab2 = L2Panel(self, id=1)
        attribList = (glcanvas.WX_GL_RGBA, glcanvas.WX_GL_DOUBLEBUFFER, glcanvas.WX_GL_DEPTH_SIZE, 24)
        self.m_canvas = Canvas(self, 2, attribList)

        s = wx.GridBagSizer(0, 0)
        s.Add(self.m_lab1, flag=wx.EXPAND | (wx.ALL - wx.BOTTOM), pos=(0, 0), border=10)
        s.Add(wx.StaticLine(self), flag=wx.EXPAND | (wx.ALL - wx.BOTTOM), pos=(1, 0), border=10)
        s.Add(self.m_lab2, flag=wx.EXPAND | wx.ALL, pos=(2, 0), border=10)
        s.Add(self.m_canvas, flag=wx.ALL | wx.EXPAND, pos=(0, 1), span=(3, 1), border=10)

        s.AddGrowableCol(1)
        s.AddGrowableRow(2)

        self.SetSizer(s)

        self.m_lab2.m_xO_sl.Disable()
        self.m_lab2.m_yO_sl.Disable()
        self.m_lab2.m_alpha_cmb.Disable()
        self.m_lab2.m_alpha_sc.Disable()
        self.m_lab2.m_alpha_sl.Disable()
        self.m_lab2.m_mixingS_cmb.Disable()
        self.m_lab2.m_mixingD_cmb.Disable()

        self.Bind(wx.EVT_CHECKBOX, self.CheckBoxHandler)
        self.Bind(wx.EVT_COMBOBOX, self.ComboBoxHandler)
        self.Bind(wx.EVT_SLIDER, self.SliderHandler)
        self.Bind(wx.EVT_SPINCTRL, self.SpinCtrlHandler)

    def CheckBoxHandler(self, event: wx.Event):
        enable = event.GetEventObject().IsChecked()
        if event.GetId() == 200:
            self.m_canvas.secondDraw = enable
        elif event.GetId() == 201:
            self.m_lab2.m_xO_sl.Enable(enable)
            self.m_lab2.m_yO_sl.Enable(enable)
            self.m_canvas.onClipping[0] = enable
        elif event.GetId() == 202:
            self.m_lab2.m_alpha_cmb.Enable(enable)
            self.m_lab2.m_alpha_sc.Enable(enable)
            self.m_lab2.m_alpha_sl.Enable(enable)
            self.m_canvas.onTransparenting[0] = enable
        elif event.GetId() == 203:
            self.m_lab2.m_mixingS_cmb.Enable(enable)
            self.m_lab2.m_mixingD_cmb.Enable(enable)
            self.m_canvas.onMixing[0] = enable
        self.m_canvas.OnDraw()
        event.Skip()

    def ComboBoxHandler(self, event: wx.Event):
        widget: wx.ComboBox = event.GetEventObject()
        if event.GetId() == 300:
            self.m_canvas.primitiveType = primitives[widget.GetValue()]
        elif event.GetId() == 301:
            self.m_canvas.onTransparenting[2] = alphaType[widget.GetValue()]
        elif event.GetId() == 302:
            self.m_canvas.onMixing[1] = mixingSrc[widget.GetValue()]
        elif event.GetId() == 303:
            self.m_canvas.onMixing[2] = mixingDst[widget.GetValue()]
        self.m_canvas.OnDraw()
        event.Skip()

    def SliderHandler(self, event: wx.Event):
        widget: wx.Slider = event.GetEventObject()
        if event.GetId() == 400:
            self.m_lab2.m_xPos_st.SetLabel(f'{widget.GetValue()} %')
            self.m_canvas.onClipping[1] = int(widget.GetValue())
        elif event.GetId() == 401:
            self.m_lab2.m_yPos_st.SetLabel(f'{widget.GetValue()} %')
            self.m_canvas.onClipping[2] = int(widget.GetValue())
        elif event.GetId() == 402:
            self.m_lab2.m_alpha_st.SetLabel(f'{widget.GetValue()} %')
            self.m_canvas.onTransparenting[1] = int(widget.GetValue())
        self.m_canvas.OnDraw()
        event.Skip()

    def SpinCtrlHandler(self, event: wx.Event):
        widget: wx.SpinCtrl = event.GetEventObject()
        if event.GetId() == 500:
            self.m_canvas.onTransparenting[3] = int(widget.GetValue())
        self.m_canvas.OnDraw()
        event.Skip()


if __name__ == '__main__':
    app = wx.App()
    frame = MyFrame(None, 'Lab1-2')
    frame.Show()
    app.MainLoop()
