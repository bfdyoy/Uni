#include "Vignere.h"

int main()
{
    char option;
    while (true)
    {
        cout << "Press 1 to encrypt a string.\n";
        cout << "Press 2 to decrypt a string.\n";
        cout << "Press anything else to exit\n";
        cout << "Choose what you want to do next\n";
        cin >> option;
        string key, text;
        string encrypted_text, decrypted_text;
        char encrypted_character, decrypted_character;
        
        if (option == '1')
        {
            cout << "Text to encrypt = ";
            cin >> text;
            cout << "Key = ";
            cin >> key; 
            int it = 0;
            key = generateKey(text, key);

            it = 0;
            for_each(
                execution::par_unseq,
                text.begin(),
                text.end(),
                [&](auto const& val)
                {
                    encrypted_text.push_back(vigenere_encrypt(val, key[it++]));
                }
            );
            cout << encrypted_text << endl;
            
        }
        else if (option == '2')
        {
            cout << "Text to decrypt = ";
            cin >> text;
            cout << "Key = ";
            cin >> key;
            int it = 0;
            key = generateKey(text, key);
            for_each(
                execution::par_unseq,
                text.begin(),
                text.end(),
                [&](auto const& val)
                {
                    decrypted_text.push_back(vigenere_decrypt(val, key[it++]));
                }
            );
            cout << decrypted_text << endl;
        }
        else
        {
            break;
        }
    }
    return 0;
}
