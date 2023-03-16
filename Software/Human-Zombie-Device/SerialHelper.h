// Enables to write to Serial like this
// Serial << "text" << variable << '\n'
template <typename T>
Print& operator<<(Print& printer, T value)
{
    printer.print(value);
    return printer;
}
