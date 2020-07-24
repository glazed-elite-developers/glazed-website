type developer = {
  key: string,
  name: string,
  skills: array(string),
  description: string,
  shortDescription: string,
  linkedIn: string,
};

type square =
  | TitleSquare(string)
  | MottoSquare(string)
  | SendApplicationSquare
  | DeveloperSquare(string);

module DeveloperComparable =
  Belt.Id.MakeComparable({
    type t = string;
    let cmp = Pervasives.compare;
  });

let developers =
  Belt.Map.fromArray(
    ~id=(module DeveloperComparable),
    [|
      (
        "matias",
        {
          key: "matias",
          name: "Carlos Matias",
          skills: [|"React", "GraphQL", "Gatsby", "Node"|],
          description: "",
          shortDescription: "",
          linkedIn: "",
        },
      ),
      (
        "cristiano",
        {
          key: "cristiano",
          name: "Cristiano Alves",
          skills: [|"iOS", "Android", "IOT"|],
          description: "",
          shortDescription: "",
          linkedIn: "",
        },
      ),
      (
        "diogo",
        {
          key: "diogo",
          name: "Diogo Nunes",
          skills: [|"iOS", "IOT"|],
          description: "He has an unmatched attention to detail, shipped a ton of apps and he's very efficient, so you won't see a bad app coming out of his hands.",
          shortDescription: "Diogo Has a vast experience and deep knowledge on all things iOS.",
          linkedIn: "https://www.linkedin.com/in/diogocamposnunes/",
        },
      ),
      (
        "filipe",
        {
          key: "filipe",
          name: {j|Filipe Perdigão|j},
          skills: [|"Node", "Javascript", "Rails"|],
          description: "",
          shortDescription: "",
          linkedIn: "",
        },
      ),
      (
        "ismael",
        {
          key: "ismael",
          name: "Ismael Abreu",
          skills: [|"Rails", "Elixir", "Node", "Javascript"|],
          description: "",
          shortDescription: "",
          linkedIn: "",
        },
      ),
      (
        "rick",
        {
          key: "rick",
          name: "Ricardo Moutinho",
          skills: [|"Android", "IOT", "Javascript"|],
          description: "",
          shortDescription: "",
          linkedIn: "",
        },
      ),
      (
        "figo",
        {
          key: "figo",
          name: "Rui Monteiro",
          skills: [|"React", "Elm", "Javascript", "Node", "ECommerce"|],
          description: "",
          shortDescription: "",
          linkedIn: "",
        },
      ),
      (
        "miguel",
        {
          key: "miguel",
          name: "Miguel Quintas",
          skills: [|"iOS", "Android", "React Native", "React", "Django"|],
          description: "",
          shortDescription: "",
          linkedIn: "",
        },
      ),
      (
        "joao",
        {
          key: "joao",
          name: {j|João Barbosa|j},
          skills: [|"iOS", "Android", "Django"|],
          description: "",
          shortDescription: "",
          linkedIn: "",
        },
      ),
      (
        "nelson",
        {
          key: "nelson",
          name: "Nelson Sachse",
          skills: [|"iOS", "Android", "Strategy", "Startups"|],
          description: "",
          shortDescription: "",
          linkedIn: "",
        },
      ),
      (
        "nuno",
        {
          key: "nuno",
          name: "Nuno Silva",
          skills: [|"iOS", "Android", "C++", "Django"|],
          description: "",
          shortDescription: "",
          linkedIn: "",
        },
      ),
      (
        "goncalo",
        {
          key: "goncalo",
          name: {j|Gonçalo Lobo|j},
          skills: [|"React", "React Native", "Rails", "GraphQL", "Node"|],
          description: "",
          shortDescription: "",
          linkedIn: "",
        },
      ),
      (
        "torres",
        {
          key: "torres",
          name: "Pedro Torres",
          skills: [|"Django", "React", "Full stack", "Node"|],
          description: "",
          shortDescription: "",
          linkedIn: "",
        },
      ),
      (
        "jose",
        {
          key: "jose",
          name: {j|José Magalhães|j},
          skills: [|"AI", "IOT", "Machine Learning", "Backend", "Java", "Javascript"|],
          description: "",
          shortDescription: "",
          linkedIn: "",
        },
      ),
      (
        "pedro",
        {
          key: "pedro",
          name: "Pedro Campos",
          skills: [|"Javasctipt", "iOS", "Android", "Django", "Node"|],
          description: "",
          shortDescription: "",
          linkedIn: "",
        },
      ),
      (
        "raspa",
        {
          key: "raspa",
          name: "Pedro Santos",
          skills: [|"iOS", "Javascript", "React", "Django", "Node"|],
          description: "",
          shortDescription: "",
          linkedIn: "",
        },
      ),
      (
        "maria",
        {
          key: "maria",
          name: "Maria Vasquez",
          skills: [|
            "Partnerships",
            "Clients",
            "Office",
            "Culture",
            "Communication",
            "Accounting",
          |],
          description: "",
          shortDescription: "",
          linkedIn: "",
        },
      ),
      (
        "daniela",
        {
          key: "daniela",
          name: "Daniela Dias",
          skills: [|"iOS", "React Native", "React", "Angular"|],
          description: "",
          shortDescription: "",
          linkedIn: "",
        },
      ),
    |],
  );

let squares = [|
  TitleSquare("// team"),
  DeveloperSquare("matias"),
  DeveloperSquare("cristiano"),
  DeveloperSquare("diogo"),
  DeveloperSquare("filipe"),
  DeveloperSquare("ismael"),
  MottoSquare("Great developers build great code"),
  DeveloperSquare("rick"),
  DeveloperSquare("figo"),
  DeveloperSquare("miguel"),
  DeveloperSquare("joao"),
  DeveloperSquare("daniela"),
  DeveloperSquare("nuno"),
  DeveloperSquare("goncalo"),
  MottoSquare("Great developers love their work"),
  SendApplicationSquare,
  DeveloperSquare("torres"),
  DeveloperSquare("jose"),
  DeveloperSquare("pedro"),
  DeveloperSquare("raspa"),
  DeveloperSquare("maria"),
  DeveloperSquare("nelson"),
|];
