#ifndef _EXPORT_HPP_
#define _EXPORT_HPP_

#ifdef _WIN32

// Sur Windows, les symboles s'exportent avec l'attribut dllexport mais doivent s'importer avec dllimport
// On utilise donc un define lors de la compilation du moteur (qui ne sera pas pr�sent � son utilisation) pour les distinguer

#ifdef GE2DX_ENGINE_BUILD
#define GE2DX_ENGINE_API __declspec(dllexport)
#else
#define GE2DX_ENGINE_API __declspec(dllimport)
#endif

#else

// Sur les autres syst�mes, rendre le symbole visible suffit � l'import comme � l'export

#define GE2DX_ENGINE_API __attribute__((visibility("default")))

#endif

#endif // !_EXPORT_HPP_