[@react.component]
let make = () => {
  <Layout>
    <PageLayout useDarkNavBarLinks=true>
      <h1> {React.string("NOT FOUND")} </h1>
      <p>
        {React.string(
           "You just hit a route that doesn&#39;t exist... the sadness.",
         )}
      </p>
    </PageLayout>
  </Layout>;
};

let default = make;