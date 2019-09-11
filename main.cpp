#include <string>

// https://akrzemi1.wordpress.com/2011/10/05/using-stdterminate/

[[noreturn]] void terminate_handler() noexcept
{
    if (auto exc = std::current_exception())
    {
        // we have an exception
        try
        {
            rethrow_exception(exc); // throw to recognize the type
        }
        catch (std::exception const &exc)
        {
            auto const &what = exc.what();
            if (what)
            {
                std::string s = "terminate_handler: ";
                s += what;
                printf("%s\n", s.c_str());
            }
        }
        catch (...)
        {
            printf("\"terminate_handler: what() is empty\"\n");
        }
    }
    std::_Exit(EXIT_FAILURE);
}

int main()
{
    std::set_terminate(&terminate_handler);

    std::string volume;
    int v = std::stoi(volume);
    return v;
}
