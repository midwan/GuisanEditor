class DummyListModel : public gcn::ListModel
{
    private:
        std::string     mStrings[10];
    public:
        DummyListModel();
        ~DummyListModel();
        int getNumberOfElements();
        std::string getElementAt(int i);
};
