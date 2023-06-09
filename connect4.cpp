#include <wx/wx.h>
#include <wx/bitmap.h>

// Define constants
const int CELL_SIZE = 80;
const int NUM_ROWS = 6;
const int NUM_COLS = 7;
const wxString PLAYER_ONE_SYMBOL = "X";
const wxString PLAYER_TWO_SYMBOL = "O";

// Declare ConnectFourFrame class
class ConnectFourFrame : public wxFrame {
public:
    ConnectFourFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(NUM_COLS * CELL_SIZE, NUM_ROWS * CELL_SIZE)) {
        // Initialize game state
        currentPlayer = 1;
        board = new int*[NUM_ROWS];
        for (int i = 0; i < NUM_ROWS; i++) {
            board[i] = new int[NUM_COLS];
            for (int j = 0; j < NUM_COLS; j++) {
                board[i][j] = 0;
            }
        }

        // Connect events
        Connect(wxEVT_PAINT, wxPaintEventHandler(ConnectFourFrame::OnPaint));
        Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(ConnectFourFrame::OnMouseClick));
    }

    void OnPaint(wxPaintEvent& event) {
        wxPaintDC dc(this);
        DrawBoard(dc);
        DrawPieces(dc);
    }

    void OnMouseClick(wxMouseEvent& event) {
        int col = event.GetX() / CELL_SIZE;
        if (CanPlayMove(col)) {
            int row = GetNextAvailableRow(col);
            board[row][col] = currentPlayer;
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
            Refresh();
        }
    }

    bool CanPlayMove(int col) const {
        return (board[0][col] == 0);
    }

    int GetNextAvailableRow(int col) const {
        for (int i = NUM_ROWS - 1; i >= 0; i--) {
            if (board[i][col] == 0) {
                return i;
            }
        }
        return -1; // Invalid row
    }

    void DrawBoard(wxDC& dc) const {
        dc.SetBackground(*wxWHITE_BRUSH);
        dc.Clear();
        dc.SetPen(*wxBLACK_PEN);
        for (int i = 1; i < NUM_COLS; i++) {
            dc.DrawLine(i * CELL_SIZE, 0, i * CELL_SIZE, NUM_ROWS * CELL_SIZE);
        }
        for (int i = 1; i < NUM_ROWS; i++) {
            dc.DrawLine(0, i * CELL_SIZE, NUM_COLS * CELL_SIZE, i * CELL_SIZE);
        }
    }

    void DrawPieces(wxDC& dc) const {
        for (int i = 0; i < NUM_ROWS; i++) {
            for (int j = 0; j < NUM_COLS; j++) {
                if (board[i][j] != 0) {
                    int x = j * CELL_SIZE;
                    int y = (NUM_ROWS - i - 1) * CELL_SIZE;
                    if (board[i][j] == 1) {
                        dc.SetBrush(*wxRED_BRUSH);
                    } else {
                        dc.SetBrush(*wxYELLOW_BRUSH);
                    }
                    dc.DrawEllipse(x + 10, y + 10, CELL_SIZE - 20, CELL_SIZE - 20);
                }
            }
        }
    }

private:
    int currentPlayer;
    int** board;
};

class ConnectFourApp : public wxApp {
public:
    virtual bool OnInit() {
        ConnectFourFrame* frame = new ConnectFourFrame("Connect Four");
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(ConnectFourApp);

