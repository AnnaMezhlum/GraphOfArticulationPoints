int main() {
    Graph obj;

    obj.insertGraph("input.txt");
    obj.findAPs_Tarjan();
    obj.print();
    obj.printAP();
    return 0;
}
