type developer = {
  name: string,
  skills: array(string),
  photoKey: string,
  description: string,
  shortDescription: string,
  linkedIn: string,
};

type square =
  | TitleSquare(string)
  | MottoSquare(string)
  | SendApplicationSquare
  | DeveloperSquare(developer);

let squares = [|
  TitleSquare("// team"),
  DeveloperSquare({
    name: "Cristiano Alves",
    skills: [|"iOS", "Android", "IOT"|],
    photoKey: "carlosMatias",
    description: "",
    shortDescription: "",
    linkedIn: "",
  }),
  DeveloperSquare({
    name: "Diogo Nunes",
    skills: [|"iOS", "IOT"|],
    photoKey: "carlosMatias",
    description: "",
    shortDescription: "",
    linkedIn: "",
  }),
  DeveloperSquare({
    name: {j|Filipe Perdigão|j},
    skills: [|"Node", "Javascript", "Rails"|],
    photoKey: "carlosMatias",
    description: "",
    shortDescription: "",
    linkedIn: "",
  }),
  DeveloperSquare({
    name: "Ismael Abreu",
    skills: [|"Rails", "Elixir", "Node", "Javascript"|],
    photoKey: "carlosMatias",
    description: "",
    shortDescription: "",
    linkedIn: "",
  }),
  DeveloperSquare({
    name: "Ricardo Moutinho",
    skills: [|"Android", "IOT", "Javascript"|],
    photoKey: "carlosMatias",
    description: "",
    shortDescription: "",
    linkedIn: "",
  }),
  MottoSquare("Great developers build great code"),
  DeveloperSquare({
    name: "Rui Monteiro",
    skills: [|"React", "Elm", "Javascript", "Node", "ECommerce"|],
    photoKey: "carlosMatias",
    description: "",
    shortDescription: "",
    linkedIn: "",
  }),
  DeveloperSquare({
    name: "Miguel Quintas",
    skills: [|"iOS", "Android", "React Native", "React", "Django"|],
    photoKey: "carlosMatias",
    description: "",
    shortDescription: "",
    linkedIn: "",
  }),
  DeveloperSquare({
    name: {j|João Barbosa|j},
    skills: [|"iOS", "Android", "Django"|],
    photoKey: "carlosMatias",
    description: "",
    shortDescription: "",
    linkedIn: "",
  }),
  DeveloperSquare({
    name: "Nuno Silva",
    skills: [|"iOS", "Android", "C++", "Django"|],
    photoKey: "carlosMatias",
    description: "",
    shortDescription: "",
    linkedIn: "",
  }),
  DeveloperSquare({
    name: {j|Gonçalo Lobo|j},
    skills: [|"React", "React Native", "Rails", "GraphQL", "Node"|],
    photoKey: "carlosMatias",
    description: "",
    shortDescription: "",
    linkedIn: "",
  }),
  MottoSquare("Great developers love their work"),
  DeveloperSquare({
    name: "Pedro Torres",
    skills: [|"Django", "React", "Full stack", "Node"|],
    photoKey: "carlosMatias",
    description: "",
    shortDescription: "",
    linkedIn: "",
  }),
  DeveloperSquare({
    name: {j|José Magalhães|j},
    skills: [|"AI", "IOT", "Machine Learning", "Backend", "Java", "Javascript"|],
    photoKey: "carlosMatias",
    description: "",
    shortDescription: "",
    linkedIn: "",
  }),
  SendApplicationSquare,
  DeveloperSquare({
    name: "Pedro Campos",
    skills: [|"Javasctipt", "iOS", "Android", "Django", "Node"|],
    photoKey: "carlosMatias",
    description: "",
    shortDescription: "",
    linkedIn: "",
  }),
  DeveloperSquare({
    name: "Pedro Santos",
    skills: [|"iOS", "Javascript", "React", "Django", "Node"|],
    photoKey: "carlosMatias",
    description: "",
    shortDescription: "",
    linkedIn: "",
  }),
  DeveloperSquare({
    name: "Maria Vasquez",
    skills: [|"Partnerships", "Clients", "Office", "Culture", "Communication", "Accounting"|],
    photoKey: "carlosMatias",
    description: "",
    shortDescription: "",
    linkedIn: "",
  }),
|];
